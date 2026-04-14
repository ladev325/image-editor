#include "Layer.h"

Layer::Layer() : Layer({300, 300}) {}
Layer::Layer(sf::Vector2u size)
    : render_texture(size),
      sprite(render_texture.getTexture()) {
  render_texture.clear(sf::Color::Transparent);
  render_texture.display();
}

void Layer::setSize(sf::Vector2u size) {
  sf::RenderTexture old_texture(render_texture.getSize());
  sf::Sprite old_sprite(old_texture.getTexture());

  old_texture.clear(sf::Color::Transparent);
  old_texture.draw(sprite, sf::BlendNone);
  old_texture.display();

  if (render_texture.resize(size)) {
    render_texture.clear(sf::Color::Transparent);
    render_texture.draw(old_sprite, sf::BlendNone);
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
