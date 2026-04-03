#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Shadered {
private:
  sf::Shader shader;

protected:
  Shadered();
  Shadered(std::string path);
  virtual ~Shadered() = default;
  sf::Shader *getShader();
};