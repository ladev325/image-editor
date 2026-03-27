/*#include "Pencil.h"
#include <cmath>
#include <iostream>

Pencil::Pencil(PencilConfig config)
    : Moded(config.mode), Colored(config.color),
      prev_pos({0, 0}), is_down(false) {}

void Pencil::updateTexture(sf::RenderTexture &render_texture) const {
  render_texture.clear(sf::Color::Transparent);
  render_texture.draw(snapshot_sprite);
  render_texture.draw(buffer_sprite);
  render_texture.display();
}

bool Pencil::onMouseDown(sf::RenderTexture &render_texture,
                         sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  snapshot_texture.clear(sf::Color::Transparent);
  snapshot_texture.draw(sf::Sprite(render_texture.getTexture()));
  snapshot_texture.display();

  is_down = true;
  prev_pos = {(int)std::floor(texture_pos.x), (int)std::floor(texture_pos.y)};
  sf::Vertex pixel = {sf::Vector2f(prev_pos) + sf::Vector2f(0.5f, 0.5f),
                      sf::Color::White};

  buffer_texture.clear(sf::Color::Transparent);
  buffer_texture.draw(&pixel, 1, sf::PrimitiveType::Points);
  buffer_texture.display();
  buffer_sprite.setColor(getColor());

  updateTexture(render_texture);
  return true;
}

bool Pencil::onMouseUp(sf::RenderTexture &render_texture,
                       sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  is_down = false;
  return false;
}

bool Pencil::onMouseMove(sf::RenderTexture &render_texture,
                         sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_down) {
    sf::Vector2i texture_pos_i{(int)std::floor(texture_pos.x),
                               (int)std::floor(texture_pos.y)};
    if (prev_pos != texture_pos_i) {
      sf::Vector2f center_offset = sf::Vector2f(0.5f, 0.5f);
      sf::VertexArray line(sf::PrimitiveType::Lines, 2);
      line[0] = {sf::Vector2f(prev_pos) + center_offset,
                 sf::Color::White};
      line[1] = {sf::Vector2f(texture_pos_i) + center_offset,
                 sf::Color::White};
      sf::Vertex pixel = {sf::Vector2f(texture_pos_i) + center_offset,
                          sf::Color::White};

      buffer_texture.draw(line);
      buffer_texture.draw(&pixel, 1, sf::PrimitiveType::Points);
      buffer_texture.display();
      buffer_sprite.setColor(getColor());

      updateTexture(render_texture);
      prev_pos = texture_pos_i;
    }
    return true;
  }
  return false;
}*/