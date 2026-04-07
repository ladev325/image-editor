#pragma once
#include "../../base/buffered_mode/BufferedMode.h"
#include "PencilSettings.h"

class PencilMode : public BufferedMode {
private:
  PencilSettings settings;
  sf::Vector2i prev_pos;
  bool is_down;
  void updateTexture(sf::RenderTexture &render_texture);

public:
  PencilMode();
  bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
  bool onMouseUp(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                 sf::Vector2f texture_pos) override;
  bool onMouseMove(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
};
