#include "Thickened.h"

Thickened::Thickened() : thickness(4) {}
Thickened::Thickened(int thickness) : thickness(thickness) {}

void Thickened::setThickness(int thickness) {
  this->thickness = thickness;
}

int Thickened::getThickness() const {
  return thickness;
}