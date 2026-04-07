#pragma once
#include "../../base/ISettings.h"

struct BrushSettings : public ISettings {
  void drawUI() override {}

  sf::Color color = sf::Color::Blue;
  float thickness = 20;
};