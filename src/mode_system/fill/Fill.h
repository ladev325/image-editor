#pragma once
#include "../base/base.h"

enum class FillMode { Local, Global };

class Fill : public Mode, public Moded<FillMode>, public Colored, public Thresholded {
private:

public:
  Fill();
  bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
  bool onMouseUp(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                 sf::Vector2f texture_pos) override;
  bool onMouseMove(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
};
