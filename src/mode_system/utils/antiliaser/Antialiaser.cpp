#include "Antialiaser.h"
#include "constants.h"

Antialiaser::Antialiaser() : Antialiaser(1) {}
Antialiaser::Antialiaser(bool state)
    : Shaderer(Constants::Path::ShapeAAShader),
      state(state) {
  shader.setUniform("radius", Constants::ShapeAAShader::Radius);
  shader.setUniform("tight_coef", Constants::ShapeAAShader::TightCoef);
}

sf::Shader *Antialiaser::getShader() {
  return state ? &shader : nullptr;
}

void Antialiaser::setResolution(sf::Vector2f resolution) {
  shader.setUniform("resolution", resolution);
}

void Antialiaser::setState(bool state) {
  this->state = state;
}

bool Antialiaser::getState() const {
  return state;
}