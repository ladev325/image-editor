#pragma once
#include "../../base/ISettings.h"
#include <SFML/Graphics.hpp>

struct PencilSettings : public ISettings {
  void drawUI() override {}
  enum class Mode { KeepAlpha, IncreaseAlpha };
  
  Mode mode = Mode::KeepAlpha;
  sf::Color color = sf::Color::Blue;
};