#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "layer_system/viewport/Viewport.h"

// TODO: add CurrentMode(&render_texture) for texture caching on create, 
// -> cache for the next action right after onMouseDown

int main() {

  // init window
  sf::RenderWindow window(sf::VideoMode({640, 480}), "App");
  window.setVerticalSyncEnabled(true);
  if (!ImGui::SFML::Init(window)) {
    return -1;
  }

  sf::Clock delta_clock;
  sf::Vector2u window_size = window.getSize();

  Viewport viewport({1000, 1000}, {100, 100}, {1000, 1000}, 2, sf::Color::White);
  viewport.LAYER_TEST();
  //viewport.setSize({15000, 15000});

  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      ImGui::SFML::ProcessEvent(window, *event);

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      // resize
      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        window_size = resized->size;
        sf::Vector2f window_size_f = sf::Vector2f(window_size);

        sf::View view({0.f, 0.f}, sf::Vector2f(window_size));
        view.setCenter(sf::Vector2f(window_size) / 2.f);
        window.setView(view);

        viewport.setFrameSize(window_size_f * 0.9f);
        viewport.setPosition((window_size_f - viewport.getFrameSize()) / 2.f);
      }

      viewport.tick(*event, window);
    }

    ImGui::SFML::Update(window, delta_clock.restart());
    window.clear();
    viewport.render(window);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  return 0;
}