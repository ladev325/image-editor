#pragma once
#include <SFML/Graphics.hpp>

class Colored {
private:
  sf::Color color;

protected:
  Colored();
  Colored(sf::Color color);
  virtual ~Colored() = default;
  void setColor(sf::Color color);
  sf::Color getColor() const;
};