#include "Antialiaser.h"
#include "constants.h"

Antialiaser::Antialiaser()
    : Shaderer(Constants::Path::ShapeAAShader) {
  shader.setUniform("radius", Constants::ShapeAAShader::Radius);
  shader.setUniform("tight_coef", Constants::ShapeAAShader::TightCoef);
}

void Antialiaser::setResolution(sf::Vector2f resolution) {
  shader.setUniform("resolution", resolution);
}