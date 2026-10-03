#include "Layer.h"

Layer::Layer() : Layer({300, 300}) {}
Layer::Layer(sf::Vector2u size)
    : render_texture(size),
      sprite(render_texture.getTexture()) {
  render_texture.clear(sf::Color::Transparent);
  render_texture.display();
}

void Layer::setSize(sf::Vector2u size) {
  sf::RenderTexture backup_texture(render_texture.getSize());
  sf::Sprite backup_sprite(backup_texture.getTexture());

  backup_texture.clear(sf::Color::Transparent);
  backup_texture.draw(sprite, sf::BlendNone);
  backup_texture.display();

  if (render_texture.resize(size)) {
    render_texture.clear(sf::Color::Transparent);
    render_texture.draw(backup_sprite, sf::BlendNone);
    render_texture.display();
    sprite.setTexture(render_texture.getTexture(), true);
  }
}

sf::Vector2u Layer::getSize() const {
  return render_texture.getSize();
}

const sf::Sprite &Layer::getSprite() const {
  return sprite;
}

sf::RenderTexture &Layer::getRenderTexture() {
  return render_texture;
}