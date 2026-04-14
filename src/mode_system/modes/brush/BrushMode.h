#pragma once
#include "../../base/buffered_mode/BufferedMode.h"
#include "../../../utils/antialiaser/Antialiaser.h"
#include "BrushSettings.h"

class BrushMode : public BufferedMode {
private:
  BrushSettings settings;
  Antialiaser antialiaser;
  sf::Vector2i prev_pos;
  bool is_down;
  void updateTexture(sf::RenderTexture &render_texture);
  void drawPoint(sf::RenderTexture &render_texture, sf::Vector2f pos, sf::Color color);
  void drawLine(sf::RenderTexture &render_texture,
                sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color);

public:
  BrushMode();
  bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
  bool onMouseUp(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                 sf::Vector2f texture_pos) override;
  bool onMouseMove(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
};