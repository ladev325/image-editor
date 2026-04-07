#pragma once
#include "ISettings.h"
#include <SFML/Graphics.hpp>

class IMode {
public:
  virtual ~IMode() = default;
  void drawUI() {
    if (i_settings) {
      i_settings->drawUI();
    }
  }
  virtual void setTextureSize(sf::Vector2u texture_size) {}
  virtual bool onMouseDown(sf::RenderTexture &render_texture,
                           sf::Vector2f mouse_pos,
                           sf::Vector2f texture_pos) = 0;
  virtual bool onMouseUp(sf::RenderTexture &render_texture,
                         sf::Vector2f mouse_pos, sf::Vector2f texture_pos) = 0;
  virtual bool onMouseMove(sf::RenderTexture &render_texture,
                           sf::Vector2f mouse_pos,
                           sf::Vector2f texture_pos) = 0;

protected:
 ISettings* i_settings;
};