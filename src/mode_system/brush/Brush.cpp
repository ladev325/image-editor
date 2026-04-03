#include "Brush.h"
#include <cmath>

Brush::Brush()
    : Antialiased(true), Colored(sf::Color::Blue), Thickened(20),
      prev_pos({0, 0}), is_down(false) {}

void Brush::drawPoint(sf::RenderTexture &render_texture,
                    sf::Vector2f pos, sf::Color color) {
  sf::CircleShape circle(getThickness() / 2.0f);
  circle.setFillColor(color);
  circle.setOrigin({getThickness() / 2.0f, getThickness() / 2.0f});
  circle.setPosition(pos);
  buffer_texture.draw(circle);
}

void Brush::drawLine(sf::RenderTexture &render_texture,
                   sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color) {
  int x0 = (int)pos1.x, y0 = (int)pos1.y;
  int x1 = (int)pos2.x, y1 = (int)pos2.y;

  int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while (true) {
    drawPoint(buffer_texture, sf::Vector2f(x0 + 0.5f, y0 + 0.5f), color);
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void Brush::updateTexture(sf::RenderTexture &render_texture) {
  setAAResolution(sf::Vector2f(buffer_texture.getSize()));
  render_texture.clear(sf::Color::Transparent);
  render_texture.draw(snapshot_sprite);
  buffer_sprite.setColor(getColor());
  render_texture.draw(buffer_sprite, getAAShader());
  render_texture.display();
}

bool Brush::onMouseDown(sf::RenderTexture &render_texture,
                      sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  snapshot_texture.clear(sf::Color::Transparent);
  snapshot_texture.draw(sf::Sprite(render_texture.getTexture()));
  snapshot_texture.display();

  is_down = true;
  prev_pos = {(int)std::floor(texture_pos.x), (int)std::floor(texture_pos.y)};

  buffer_texture.clear(sf::Color::Transparent);
  drawPoint(buffer_texture, sf::Vector2f(prev_pos) + sf::Vector2f(0.5f, 0.5f), sf::Color::White);
  buffer_texture.display();

  updateTexture(render_texture);
  return true;
}

bool Brush::onMouseUp(sf::RenderTexture &render_texture,
                    sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  is_down = false;
  return false;
}

bool Brush::onMouseMove(sf::RenderTexture &render_texture,
                      sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_down) {
    sf::Vector2i texture_pos_i{(int)std::floor(texture_pos.x),
                               (int)std::floor(texture_pos.y)};
    if (prev_pos != texture_pos_i) {
      sf::Vector2f center_offset{0.5f, 0.5f};

      drawLine(buffer_texture, sf::Vector2f(prev_pos) + center_offset, sf::Vector2f(texture_pos_i) + center_offset, sf::Color::White);
      drawPoint(buffer_texture, sf::Vector2f(texture_pos_i) + center_offset, sf::Color::White);
      buffer_texture.display();

      updateTexture(render_texture);
      prev_pos = texture_pos_i;
    }
    return true;
  }
  return false;
}