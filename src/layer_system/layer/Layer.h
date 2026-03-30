#pragma once
#include "constants.h" // IWYU pragma: export
#include <SFML/Graphics.hpp>

class Layer {
private:
  sf::RenderTexture render_texture;
  sf::Sprite sprite;

public:
  Layer();
  Layer(sf::Vector2u resolution);

  void setSize(sf::Vector2u resolution);
  sf::Vector2u getSize() const;
  const sf::Sprite &getSprite() const;
  sf::RenderTexture &getRenderTexture();
};