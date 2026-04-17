#pragma once
#include "../../base/buffered_mode/BufferedMode.h"
#include "FillSettings.h"

class FillMode : public BufferedMode {
private:
  FillSettings settings;

public:
  FillMode();
  bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
  bool onMouseUp(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                 sf::Vector2f texture_pos) override;
  bool onMouseMove(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
};
