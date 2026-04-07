#include "PencilMode.h"
#include <cmath>

PencilMode::PencilMode()
    : BufferedMode(2),
      prev_pos({0, 0}), is_down(false) {
  i_settings = &settings;
}

void PencilMode::updateTexture(sf::RenderTexture &render_texture) {
  if (settings.mode == PencilSettings::Mode::KeepAlpha) {
    render_texture.clear(sf::Color::Transparent);
    render_texture.draw(buffer_sprites[0]);
    buffer_sprites[1].setColor(settings.color);
    render_texture.draw(buffer_sprites[1]);
  }
  render_texture.display();
}

bool PencilMode::onMouseDown(sf::RenderTexture &render_texture,
                             sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  if (settings.mode == PencilSettings::Mode::KeepAlpha) {
    buffer_textures[0]->clear(sf::Color::Transparent);
    buffer_textures[0]->draw(sf::Sprite(render_texture.getTexture()));
    buffer_textures[0]->display();
  }

  is_down = true;
  prev_pos = {(int)std::floor(texture_pos.x), (int)std::floor(texture_pos.y)};
  sf::Vertex pixel = {sf::Vector2f(prev_pos) + sf::Vector2f(0.5f, 0.5f),
                      settings.mode == PencilSettings::Mode::KeepAlpha ? sf::Color::White : settings.color};

  if (settings.mode == PencilSettings::Mode::KeepAlpha) {
    buffer_textures[1]->clear(sf::Color::Transparent);
    buffer_textures[1]->draw(&pixel, 1, sf::PrimitiveType::Points);
    buffer_textures[1]->display();
  }
  else {
    render_texture.draw(&pixel, 1, sf::PrimitiveType::Points);
  }

  updateTexture(render_texture);
  return true;
}

bool PencilMode::onMouseUp(sf::RenderTexture &render_texture,
                           sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  is_down = false;
  return false;
}

bool PencilMode::onMouseMove(sf::RenderTexture &render_texture,
                             sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_down) {
    sf::Vector2i texture_pos_i{(int)std::floor(texture_pos.x),
                               (int)std::floor(texture_pos.y)};
    if (prev_pos != texture_pos_i) {
      sf::Vector2f center_offset{0.5f, 0.5f};
      sf::Vector2f norm{0, 0};
      sf::Color color = settings.mode == PencilSettings::Mode::KeepAlpha ? sf::Color::White : settings.color;

      if (settings.mode == PencilSettings::Mode::IncreaseAlpha) {
        sf::Vector2f dir = sf::Vector2f(texture_pos_i - prev_pos);
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        norm = dir / len;
      }

      sf::VertexArray line(sf::PrimitiveType::Lines, 2);
      line[0] = {sf::Vector2f(prev_pos) + center_offset + norm, color};
      line[1] = {sf::Vector2f(texture_pos_i) + center_offset, color};
      sf::Vertex pixel = {sf::Vector2f(texture_pos_i) + center_offset, color};

      if (settings.mode == PencilSettings::Mode::KeepAlpha) {
        buffer_textures[1]->draw(line);
        buffer_textures[1]->draw(&pixel, 1, sf::PrimitiveType::Points);
        buffer_textures[1]->display();
      }
      else {
        render_texture.draw(line);
        render_texture.draw(&pixel, 1, sf::PrimitiveType::Points);
      }

      updateTexture(render_texture);
      prev_pos = texture_pos_i;
    }
    return true;
  }
  return false;
}