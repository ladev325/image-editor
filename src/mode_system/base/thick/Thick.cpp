#include "Thick.h"

Thick::Thick() : Thick(4) {}
Thick::Thick(int thickness) : thickness(thickness) {}

void Thick::setThickness(int thickness) {
  this->thickness = thickness;
}

int Thick::getThickness() const {
  return thickness;
}