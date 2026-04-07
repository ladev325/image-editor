#include "BrushMode.h"
#include <cmath>

BrushMode::BrushMode()
    : BufferedMode(2),
      prev_pos({0, 0}), is_down(false) {
  i_settings = &settings;
}

void BrushMode::drawPoint(sf::RenderTexture &render_texture,
                          sf::Vector2f pos, sf::Color color) {
  sf::CircleShape circle(settings.thickness / 2.0f);
  circle.setFillColor(color);
  circle.setOrigin({settings.thickness / 2.0f, settings.thickness / 2.0f});
  circle.setPosition(pos);
  buffer_textures[1]->draw(circle);
}

void BrushMode::drawLine(sf::RenderTexture &render_texture,
                         sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color) {
  int x0 = (int)pos1.x, y0 = (int)pos1.y;
  int x1 = (int)pos2.x, y1 = (int)pos2.y;

  int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while (true) {
    drawPoint(*buffer_textures[1], sf::Vector2f(x0 + 0.5f, y0 + 0.5f), color);
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

void BrushMode::updateTexture(sf::RenderTexture &render_texture) {
  antialiaser.setResolution(sf::Vector2f(buffer_textures[1]->getSize()));
  render_texture.clear(sf::Color::Transparent);
  render_texture.draw(buffer_sprites[0]);
  buffer_sprites[1].setColor(settings.color);
  render_texture.draw(buffer_sprites[1], antialiaser.getShader());
  render_texture.display();
}

bool BrushMode::onMouseDown(sf::RenderTexture &render_texture,
                            sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  buffer_textures[0]->clear(sf::Color::Transparent);
  buffer_textures[0]->draw(sf::Sprite(render_texture.getTexture()));
  buffer_textures[0]->display();

  is_down = true;
  prev_pos = {(int)std::floor(texture_pos.x), (int)std::floor(texture_pos.y)};

  buffer_textures[1]->clear(sf::Color::Transparent);
  drawPoint(*buffer_textures[1], sf::Vector2f(prev_pos) + sf::Vector2f(0.5f, 0.5f), sf::Color::White);
  buffer_textures[1]->display();

  updateTexture(render_texture);
  return true;
}

bool BrushMode::onMouseUp(sf::RenderTexture &render_texture,
                          sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  is_down = false;
  return false;
}

bool BrushMode::onMouseMove(sf::RenderTexture &render_texture,
                            sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && is_down) {
    sf::Vector2i texture_pos_i{(int)std::floor(texture_pos.x),
                               (int)std::floor(texture_pos.y)};
    if (prev_pos != texture_pos_i) {
      sf::Vector2f center_offset{0.5f, 0.5f};

      drawLine(*buffer_textures[1], sf::Vector2f(prev_pos) + center_offset, sf::Vector2f(texture_pos_i) + center_offset, sf::Color::White);
      drawPoint(*buffer_textures[1], sf::Vector2f(texture_pos_i) + center_offset, sf::Color::White);
      buffer_textures[1]->display();

      updateTexture(render_texture);
      prev_pos = texture_pos_i;
    }
    return true;
  }
  return false;
}