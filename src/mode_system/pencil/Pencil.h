#pragma once
#include "../buffered/Buffered.h"
#include "../moded/Moded.h"
#include "../colored/Colored.h"

class Pencil : public Buffered, public Moded<PencilMode>, public Colored {
private:
  sf::Vector2i prev_pos;
  bool is_down;
  void updateTexture(sf::RenderTexture &render_texture) const;

public:
  Pencil(PencilConfig config = {});
  bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
  bool onMouseUp(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                 sf::Vector2f texture_pos) override;
  bool onMouseMove(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
                   sf::Vector2f texture_pos) override;
};