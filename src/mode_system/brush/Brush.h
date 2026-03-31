#pragma once
#include "../base/base.h"

// too different from pencil to create a shared base, sorry bud
class Brush : public Buffered, public Colored, public Thick, public Antialiased {
private:
  sf::Vector2i prev_pos;
  bool is_down;
  void updateTexture(sf::RenderTexture &render_texture);
  void drawPoint(sf::RenderTexture &render_texture, sf::Vector2f pos, sf::Color color);
  void drawLine(sf::RenderTexture &render_texture,
                sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color);

public:
  Brush(BrushConfig config = {});
  bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
  bool onMouseUp(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                 sf::Vector2f texture_pos) override;
  bool onMouseMove(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
};