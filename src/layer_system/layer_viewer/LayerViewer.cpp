#include "LayerViewer.h"
#include <algorithm>
#include <cmath>
#include <memory>

LayerViewer::LayerViewer() : LayerViewer({300, 300}, {0, 0}, {300, 300}) {}
LayerViewer::LayerViewer(sf::Vector2u size, sf::Vector2f position,
                         sf::Vector2f frame_size, float outline_thickness,
                         sf::Color outline_color)
    : LayerContainer(size), linear_scale(1), scale(1), position(0, 0),
      prev_mouse_pos(0, 0), mouse_down(false),
      zoomed_rect_texture(sf::Vector2u(frame_size)),
      zoomed_rect_sprite(zoomed_rect_texture.getTexture()) {
  frame.setPosition(position);
  frame.setSize(frame_size);
  frame.setFillColor(sf::Color::Transparent);
  frame.setOutlineThickness(outline_thickness);
  frame.setOutlineColor(outline_color);

  PencilConfig config;
  config.color = sf::Color(0, 255, 0, 50);
  config.mode = PencilMode::IncreaseAlpha;
  mode = std::make_unique<Pencil>(config);
  mode->setTextureSize(size);
}

// --------- PRIVATE ---------

void LayerViewer::clampPosition() {
  sf::Vector2f resolution = sf::Vector2f(getSize());
  sf::Vector2f max_offset = resolution / 2.f;
  position.x = std::clamp(position.x, -max_offset.x + 1.f, max_offset.x + 1.f);
  position.y = std::clamp(position.y, -max_offset.y + 1.f, max_offset.y + 1.f);
}

sf::Vector2f LayerViewer::mouseToTexturePos(sf::Vector2f mouse_pos) const {
  sf::Vector2f frame_pos = frame.getPosition();
  sf::Vector2f frame_size = frame.getSize();
  sf::Vector2f resolution{getFullTexture().getSize()};
  sf::Vector2f view_size = frame_size / scale;
  sf::Vector2f view_pos = (resolution - view_size) / 2.f + position;
  sf::Vector2f texture_pos =
      view_pos + (mouse_pos - frame_pos) / scale - sf::Vector2f(1.f, 1.f);
  return texture_pos;
}

// --------- PRIVATE MOUSE ---------

void LayerViewer::onMouseDown(sf::Vector2f mouse_pos) {
  mouse_down = true;
  prev_mouse_pos = mouse_pos;
}

void LayerViewer::onMouseUp(sf::Vector2f mouse_pos) {
  mouse_down = false;
}

void LayerViewer::onMouseDrag(sf::Vector2f mouse_pos) {
  if (mouse_down) {
    position += (prev_mouse_pos - mouse_pos) / scale;
    clampPosition();
  }
  prev_mouse_pos = mouse_pos;
}

void LayerViewer::onMouseWheel(float delta, sf::Vector2f mouse_pos) {
  float prev_scale = scale;
  linear_scale = std::clamp(linear_scale + delta * SCALE_SPEED,
                            SCALE_LINEAR_MIN, SCALE_LINEAR_MAX);
  scale = std::pow(linear_scale, SCALE_POW);
  sf::Vector2f mouse_offset = mouse_pos - frame.getPosition() - frame.getSize() / 2.f;
  sf::Vector2f pos_diff = mouse_offset / scale - mouse_offset / prev_scale;
  position -= pos_diff;
  clampPosition();
}

// --------- PUBLIC SIZE ---------

void LayerViewer::setSize(sf::Vector2u size) {
  LayerContainer::setSize(size);
  mode->setTextureSize(size);
}

// --------- PUBLIC OUTLINE ---------

void LayerViewer::setOutlineThickness(float thickness) {
  frame.setOutlineThickness(thickness);
}
float LayerViewer::getOutlineThickness() const {
  return frame.getOutlineThickness();
}
void LayerViewer::setOutlineColor(sf::Color color) {
  frame.setOutlineColor(color);
}
sf::Color LayerViewer::getOutlineColor() const {
  return frame.getOutlineColor();
}

// --------- PUBLIC SIZE & POSITION ---------

void LayerViewer::setPosition(sf::Vector2f pos) {
  frame.setPosition(pos);
  zoomed_rect_sprite.setPosition(pos);
}
sf::Vector2f LayerViewer::getPosition() const {
  return frame.getPosition();
}

void LayerViewer::setFrameSize(sf::Vector2f size) {
  frame.setSize(size);
  clampPosition();
  if (zoomed_rect_texture.resize(sf::Vector2u(size))) {
    zoomed_rect_sprite.setTexture(zoomed_rect_texture.getTexture(), true);
  }
}
sf::Vector2f LayerViewer::getFrameSize() const {
  return frame.getSize();
}

// --------- PUBLIC RENDER ---------

void LayerViewer::LAYER_TEST() {
  sf::Texture imageTexture("src/img.png");
  sf::Sprite imageSprite(imageTexture);
  setSize(imageTexture.getSize());

  addLayer();
  setActiveLayer(0);
  sf::RenderTexture &texture = getActiveTexture();
  texture.clear(sf::Color::Black);
  texture.draw(imageSprite);
  texture.display();

  setActiveLayer(1);
  sf::RenderTexture &texture2 = getActiveTexture();
  texture2.clear(sf::Color(0, 255, 0, 0));
  texture2.display();
  setActiveLayer(0);
}

void LayerViewer::render(sf::RenderWindow &window) {
  sf::Vector2f frame_size = frame.getSize();
  const sf::RenderTexture &full_texture = getFullTexture();
  sf::Vector2f resolution{full_texture.getSize()};

  // get visible region of the texture
  sf::Vector2f view_size{frame_size.x / scale + 2.f,
                         frame_size.y / scale + 2.f};
  sf::Vector2f view_pos = (resolution - view_size) / 2.f + position;

  // get fractional pos & size to adjust position smoothly
  sf::Vector2f view_pos_i{std::floor(view_pos.x), std::floor(view_pos.y)};
  sf::Vector2f view_size_i{std::floor(view_size.x), std::floor(view_size.y)};
  sf::IntRect view_rect_i{sf::Vector2i(view_pos_i), sf::Vector2i(view_size_i)};
  sf::Vector2f pos_fract{view_pos.x - view_pos_i.x, view_pos.y - view_pos_i.y};

  // get rid of the mess outside of view_rect boundaries
  auto safe_opt = view_rect_i.findIntersection({{0, 0}, sf::Vector2i(resolution)});
  if (!safe_opt.has_value()) {
    window.draw(frame);
    return;
  }
  sf::IntRect safe_rect = *safe_opt;
  sf::Vector2f clip_size{float(safe_rect.position.x - view_pos_i.x),
                         float(safe_rect.position.y - view_pos_i.y)};

  sf::RectangleShape zoomed_rect;
  zoomed_rect.setPosition((clip_size - pos_fract) * scale);
  zoomed_rect.setSize(sf::Vector2f(safe_rect.size) * scale);
  zoomed_rect.setTextureRect(safe_rect);
  zoomed_rect.setTexture(&full_texture.getTexture());

  sf::RectangleShape inner_frame;
  inner_frame.setPosition(zoomed_rect.getPosition());
  inner_frame.setSize(zoomed_rect.getSize());
  inner_frame.setFillColor(sf::Color::Transparent);
  inner_frame.setOutlineThickness(VIEWER_INNER_FRAME_THICKNESS);
  inner_frame.setOutlineColor(VIEWER_INNER_FRAME_COLOR);

  zoomed_rect_texture.clear(VIEWER_BACKGROUND_COLOR);
  zoomed_rect_texture.draw(zoomed_rect);
  zoomed_rect_texture.draw(inner_frame);
  zoomed_rect_texture.display();

  window.draw(zoomed_rect_sprite);
  window.draw(frame);
}

bool LayerViewer::tick(sf::Event event, sf::RenderWindow &window) {
  const auto *mouse_pressed = event.getIf<sf::Event::MouseButtonPressed>();
  const auto *mouse_released = event.getIf<sf::Event::MouseButtonReleased>();
  const auto *mouse_moved = event.getIf<sf::Event::MouseMoved>();
  const auto *mouse_wheel = event.getIf<sf::Event::MouseWheelScrolled>();
  if (!mouse_pressed && !mouse_released && !mouse_moved && !mouse_wheel)
    return false;

  sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
  sf::Vector2f mouse_pos = window.mapPixelToCoords(pixel_pos);
  sf::Vector2f frame_pos = frame.getPosition();
  sf::Vector2f frame_size = frame.getSize();

  bool in_frame = true;
  if (mouse_pos.x < frame_pos.x ||
      mouse_pos.y < frame_pos.y ||
      mouse_pos.x > frame_pos.x + frame_size.x ||
      mouse_pos.y > frame_pos.y + frame_size.y) {
    in_frame = false;
  }

  // mouse down
  if (mouse_pressed) {
    if (mouse_pressed->button == sf::Mouse::Button::Right) {
      if (in_frame) {
        onMouseDown(mouse_pos);
      }
    }

    else if (mouse_pressed->button == sf::Mouse::Button::Left) {
      if (mode->onMouseDown(getActiveTexture(), mouse_pos, mouseToTexturePos(mouse_pos))) {
        display();
      }
    }
  }

  // mouse up
  if (mouse_released) {
    if (mouse_released->button == sf::Mouse::Button::Right) {
      if (in_frame) {
        onMouseUp(mouse_pos);
      }
    }

    else if (mouse_released->button == sf::Mouse::Button::Left) {
      if (mode->onMouseUp(getActiveTexture(), mouse_pos, mouseToTexturePos(mouse_pos))) {
        display();
      }
    }
  }

  // mouse move
  if (mouse_moved) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
      if (in_frame) {
        onMouseDrag(mouse_pos);
      }
    }
    else if (mode->onMouseMove(getActiveTexture(), mouse_pos, mouseToTexturePos(mouse_pos))) {
      display();
    }
  }

  // mouse wheel
  if (mouse_wheel) {
    if (mouse_wheel->wheel == sf::Mouse::Wheel::Vertical && in_frame) {
      float delta = mouse_wheel->delta;
      if (delta != 0) {
        onMouseWheel(delta, mouse_pos);
      }
    }
  }
  return true;
}