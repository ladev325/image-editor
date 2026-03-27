#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include <iostream>

#include "layer_system/layer_viewer/LayerViewer.h"

int main() {

  // init window
  sf::RenderWindow window(sf::VideoMode({640, 480}), "App");
  window.setVerticalSyncEnabled(true);
  if (!ImGui::SFML::Init(window)) {
    return -1;
  }
  sf::Clock deltaClock;

  sf::Vector2u window_size = window.getSize();

  LayerViewer layer_viewer({1000, 1000}, {100, 100}, {1000, 1000}, 2, sf::Color::White);
  layer_viewer.LAYER_TEST();
  //layer_viewer.setSize({5001, 5001});
  layer_viewer.display();

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

        layer_viewer.setFrameSize(window_size_f * 0.9f);
        layer_viewer.setPosition((window_size_f - layer_viewer.getFrameSize()) / 2.f);
      }

      layer_viewer.tick(*event, window);
    }

    // ImGui::SFML::Update(window, deltaClock.restart());
    // ImGui::Begin("Hello, world!");
    // ImGui::Button("Look at this pretty button");
    // ImGui::End();

    window.clear();
    layer_viewer.render(window);

    // ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}