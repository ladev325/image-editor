#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Shaderer {
public:
  Shaderer();
  Shaderer(std::string path);
  sf::Shader *getShader();

protected:
  sf::Shader shader;
};