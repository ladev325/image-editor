#pragma once
#include <SFML/Graphics.hpp>

class Antialiased {
private:
  std::optional<sf::Shader> shader;
  void loadShader();

protected:
  Antialiased();
  Antialiased(bool state);
  virtual ~Antialiased() = default;
  void setAAState(bool state);
  bool getAAState() const;
  void setAAResolution(sf::Vector2f resolution);
  sf::Shader *getAAShader();
};