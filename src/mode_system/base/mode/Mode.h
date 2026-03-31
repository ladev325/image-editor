#pragma once
#include <SFML/Graphics.hpp>

class Mode {
public:
  virtual void setTextureSize(sf::Vector2u texture_size) {}
  virtual bool onMouseDown(sf::RenderTexture &render_texture,
                           sf::Vector2f mouse_pos,
                           sf::Vector2f texture_pos) = 0;
  virtual bool onMouseUp(sf::RenderTexture &render_texture,
                         sf::Vector2f mouse_pos, sf::Vector2f texture_pos) = 0;
  virtual bool onMouseMove(sf::RenderTexture &render_texture,
                           sf::Vector2f mouse_pos,
                           sf::Vector2f texture_pos) = 0;
  virtual ~Mode() {}
};