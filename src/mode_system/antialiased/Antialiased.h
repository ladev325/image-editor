#pragma once
#include <SFML/Graphics.hpp>

class Antialiased {
private:
  sf::Shader shader;

public:
  Antialiased();

protected:
  void setAAResolution(sf::Vector2f resolution);
  sf::Shader &getAAShader();
};