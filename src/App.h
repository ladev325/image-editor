#pragma once
#include "core/mode_selector/ModeSelector.h"
#include "viewer_system/viewport/Viewport.h"

class App {
private:
  std::unique_ptr<IMode> mode;
  Viewport viewport;
  ModeSelector mode_selector;

public:
  App();
  void resize(sf::Vector2u size);
  void onEvent(const sf::Event &event, sf::RenderWindow &window);
  void render(sf::RenderWindow &window);
};