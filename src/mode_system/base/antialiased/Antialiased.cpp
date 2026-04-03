#include "Antialiased.h"
#include "constants.h"

Antialiased::Antialiased() {
  loadShader();
}

Antialiased::Antialiased(bool state) {
  if (state) {
    loadShader();
  }
}

void Antialiased::loadShader() {
  if (!sf::Shader::isAvailable()) {
    throw std::runtime_error("Your system does not support shaders, which is necessary for proper functioning");
  }

  shader.emplace();
  if (!shader->loadFromFile(Constants::Path::ShapeAAShader, sf::Shader::Type::Fragment)) {
    shader.reset();
    throw std::runtime_error("Error loading " + Constants::Path::ShapeAAShader);
  }

  shader->setUniform("radius", Constants::ShapeAAShader::Radius);
  shader->setUniform("tight_coef", Constants::ShapeAAShader::TightCoef);
}

void Antialiased::setAAState(bool state) {
  if (state && !shader) {
    loadShader();
  }
  if (!state && shader) {
    shader.reset();
  }
}

bool Antialiased::getAAState() const {
  return (bool)shader;
}

void Antialiased::setAAResolution(sf::Vector2f resolution) {
  if (shader) {
    shader->setUniform("resolution", resolution);
  }
}

sf::Shader *Antialiased::getAAShader() {
  return shader ? &*shader : nullptr;
}