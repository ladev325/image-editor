#pragma once
#include "../shaderer/Shaderer.h"

class Antialiaser : public Shaderer {
public:
  Antialiaser();
  void setResolution(sf::Vector2f resolution);
};