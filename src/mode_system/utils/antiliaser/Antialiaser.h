#pragma once
#include "../shaderer/Shaderer.h"

class Antialiaser : public Shaderer {
private:
  bool state;

public:
  Antialiaser();
  Antialiaser(bool state);
  sf::Shader *getShader() override;
  void setResolution(sf::Vector2f resolution);
  void setState(bool state);
  bool getState() const;
};