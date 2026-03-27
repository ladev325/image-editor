#include "Pencil.h"
#include <cmath>
#include <iostream>

Pencil::Pencil(PencilConfig config)
    : Moded(config.mode), Colored(config.color),
      prev_pos({0, 0}), is_down(false) {}

bool Pencil::onMouseDown(sf::RenderTexture &render_texture,
                         sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  is_down = true;
  prev_pos = {(int)std::floor(texture_pos.x), (int)std::floor(texture_pos.y)};
  sf::Vertex pixel = {sf::Vector2f(prev_pos) + sf::Vector2f(0.5f, 0.5f),
                      getColor()};
  render_texture.draw(&pixel, 1, sf::PrimitiveType::Points);
  render_texture.display();
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
      sf::Vector2f dir = sf::Vector2f(texture_pos_i - prev_pos);
      float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
      sf::Vector2f norm = dir / len;

      sf::VertexArray line(sf::PrimitiveType::Lines, 2);
      line[0] = {sf::Vector2f(prev_pos) + center_offset + norm,
                 getColor()};
      line[1] = {sf::Vector2f(texture_pos_i) + center_offset,
                 getColor()};
      sf::Vertex pixel = {sf::Vector2f(texture_pos_i) + center_offset,
                          getColor()};

      render_texture.draw(line);
      render_texture.draw(&pixel, 1, sf::PrimitiveType::Points);
      render_texture.display();
      prev_pos = texture_pos_i;
    }
    return true;
  }
  return false;
}