#pragma once
#include "../../base/ISettings.h"
#include <SFML/Graphics.hpp>

struct FillSettings : public ISettings {
  void drawUI() override {}
  enum class Mode { Local, Global };
  
  Mode mode = Mode::Local;
  sf::Color color = sf::Color::Blue;
  float threshold = 0.4;
};