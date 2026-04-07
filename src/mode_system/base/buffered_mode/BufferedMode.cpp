#include "BufferedMode.h"

BufferedMode::BufferedMode() : BufferedMode(0) {}
BufferedMode::BufferedMode(int num_buffers, sf::Vector2u texture_size) {
  for (int i = 0; i < num_buffers; i++) {
    buffer_textures.emplace_back(std::make_unique<sf::RenderTexture>(texture_size));
    buffer_sprites.emplace_back(sf::Sprite(buffer_textures[i]->getTexture()));
  }
}

void BufferedMode::setTextureSize(sf::Vector2u texture_size) {
  for (int i = 0; i < buffer_textures.size(); i++) {
    if (buffer_textures[i]->resize(texture_size)) {
      buffer_sprites[i].setTexture(buffer_textures[i]->getTexture(), true);
    }
  }
}