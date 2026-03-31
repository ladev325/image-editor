#include "Colored.h"

Colored::Colored() : Colored(sf::Color::Red) {}
Colored::Colored(sf::Color color) : color(color) {}

void Colored::setColor(sf::Color color) {
  this->color = color;
}

sf::Color Colored::getColor() const {
  return color;
}