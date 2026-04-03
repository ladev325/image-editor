#include "Shadered.h"

Shadered::Shadered() : Shadered("shader.frag") {}
Shadered::Shadered(std::string path) {
  if (!sf::Shader::isAvailable()) {
    throw std::runtime_error("Your system does not support shaders, which is necessary for proper functioning");
  }

  if (!shader.loadFromFile(path, sf::Shader::Type::Fragment)) {
    throw std::runtime_error("Error loading " + path);
  }
}

sf::Shader *Shadered::getShader() {
  return &shader;
}