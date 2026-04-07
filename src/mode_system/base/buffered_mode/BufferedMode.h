#pragma once
#include "../IMode.h"
#include <vector>

class BufferedMode : public IMode {
public:
  BufferedMode();
  BufferedMode(int num_buffers, sf::Vector2u texture_size = {300, 300});
  void setTextureSize(sf::Vector2u texture_size) override;

protected:
  std::vector<std::unique_ptr<sf::RenderTexture>> buffer_textures;
  std::vector<sf::Sprite> buffer_sprites;
};