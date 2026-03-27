#include "Buffered.h"

Buffered::Buffered() : Buffered({300, 300}) {}
Buffered::Buffered(sf::Vector2u texture_size)
    : snapshot_texture(texture_size),
      snapshot_sprite(snapshot_texture.getTexture()),
      buffer_texture(texture_size),
      buffer_sprite(buffer_texture.getTexture()) {
}

void Buffered::setTextureSize(sf::Vector2u texture_size) {
  if (snapshot_texture.resize(texture_size)) {
    snapshot_sprite.setTexture(snapshot_texture.getTexture(), true);
  }
  if (buffer_texture.resize(texture_size)) {
    buffer_sprite.setTexture(buffer_texture.getTexture(), true);
  }
}