#include "Antialiased.h"
#include "constants.h"

Antialiased::Antialiased() {
  if (!sf::Shader::isAvailable()) {
    throw std::runtime_error("Your system does not support shaders, which is necessary for proper functioning");
  }
  if (!shader.loadFromFile(Constants::Path::ShapeAA, sf::Shader::Type::Fragment)) {
    throw std::runtime_error("Error loading " + Constants::Path::ShapeAA);
  }
  shader.setUniform("radius", Constants::ShapeAA::Radius);
  shader.setUniform("tight_coef", Constants::ShapeAA::TightCoef);
}

void Antialiased::setAAResolution(sf::Vector2f resolution) {
  shader.setUniform("resolution", resolution);
}

sf::Shader &Antialiased::getAAShader() {
  return shader;
}