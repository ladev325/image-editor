#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "App.h"
#include "global.h"

// TODO: add CurrentMode(&render_texture) for texture caching on create,
// -> cache for the next action right after onMouseDown

int main() {
  // init window
  sf::RenderWindow window(sf::VideoMode({640, 480}), "App");
  window.setVerticalSyncEnabled(true);
  if (!ImGui::SFML::Init(window)) {
    return -1;
  }

  // vars
  sf::Clock delta_clock;
  AssetManager::setRoot("assets/");
  App app;

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      // resize
      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        sf::View view({0.f, 0.f}, sf::Vector2f(resized->size));
        view.setCenter(sf::Vector2f(resized->size) / 2.f);
        window.setView(view);
        app.resize(resized->size);
      }

      app.onEvent(*event, window);
    }

    ImGui::SFML::Update(window, delta_clock.restart());
    window.clear();
    app.render(window);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}