#include "App.h"

App::App()
    : mode(std::make_unique<FillMode>()),
      viewport(mode, {1000, 1000}, {100, 100}, {1000, 1000}, 2, sf::Color::White),
      mode_selector(mode) {
  viewport.LAYER_TEST();
}

void App::resize(sf::Vector2u size) {
  sf::Vector2f size_f = sf::Vector2f(size);

  // viewport size
  sf::Vector2f viewport_size = size_f * 0.7f;
  viewport.setFrameSize(viewport_size);

  // viewport pos
  sf::Vector2f viewport_pos = (size_f - viewport_size) / 2.f;
  viewport_pos = {viewport_pos.x, viewport_pos.y * 1.3f};
  viewport.setPosition(viewport_pos);
}

void App::onEvent(const sf::Event &event, sf::RenderWindow &window) {
  viewport.onEvent(event, window);
}

void App::render(sf::RenderWindow &window) {
  viewport.render(window);

  // mode-specific settings
  const ImGuiWindowFlags flags =
      ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoScrollbar |
      ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoCollapse;

  ImGui::SetNextWindowPos(ImVec2(10, viewport.getPosition().y - viewport.getOutlineThickness()));
  ImGui::SetNextWindowSize(ImVec2(viewport.getPosition().x - 20, viewport.getFrameSize().y));
  ImGui::Begin("Mode settings", 0, flags);
  mode->drawUI();
  ImGui::End();


  // mode selector
  ImGui::SetNextWindowPos(ImVec2(viewport.getPosition().x, 10));
  ImGui::SetNextWindowSize(ImVec2(viewport.getFrameSize().x, viewport.getPosition().y - 20));
  ImGui::Begin("Mode select", 0, flags);
  if (mode_selector.drawUI()) {
    mode->setTextureSize(viewport.getSize());
  }
  ImGui::End();
}