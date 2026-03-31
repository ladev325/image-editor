#pragma once
#include <SFML/Graphics.hpp>

class Colored {
private:
  sf::Color color;

public:
  Colored();
  Colored(sf::Color color);
  void setColor(sf::Color color);
  sf::Color getColor() const;
};