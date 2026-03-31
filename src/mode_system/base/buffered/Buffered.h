#pragma once
#include "../mode/Mode.h"

class Buffered : public Mode {
public:
  Buffered();
  Buffered(sf::Vector2u texture_size);
  void setTextureSize(sf::Vector2u texture_size) override;

protected:
  sf::RenderTexture snapshot_texture;
  sf::RenderTexture buffer_texture;
  sf::Sprite snapshot_sprite;
  sf::Sprite buffer_sprite;
};