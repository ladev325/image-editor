#pragma once
#include "../Mode.h"

class BufferedMode : public Mode {
public:
  BufferedMode();
  BufferedMode(sf::Vector2u texture_size);
  void setTextureSize(sf::Vector2u texture_size) override;

protected:
  sf::RenderTexture snapshot_texture;
  sf::RenderTexture buffer_texture;
  sf::Sprite snapshot_sprite;
  sf::Sprite buffer_sprite;
};