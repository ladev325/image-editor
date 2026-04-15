#pragma once
#include "../../base/ISettings.h"
#include <SFML/Graphics.hpp>

struct PencilSettings : public ISettings {
  void drawUI() override {
    const char *mode_list[] = {"Keep alpha", "Increase alpha"};
    ImGui::Combo("Alpha mode", reinterpret_cast<int *>(&mode), mode_list, IM_ARRAYSIZE(mode_list));

    float temp_color[] = {
        color.r / 255.f,
        color.g / 255.f,
        color.b / 255.f,
        color.a / 255.f};

    if (ImGui::ColorEdit4("Fill color", temp_color, ImGuiColorEditFlags_NoInputs)) {
      color.r = temp_color[0] * 255.f;
      color.g = temp_color[1] * 255.f;
      color.b = temp_color[2] * 255.f;
      color.a = temp_color[3] * 255.f;
    }
  }
  enum class Mode { KeepAlpha,
                    IncreaseAlpha };

  Mode mode = Mode::KeepAlpha;
  sf::Color color = sf::Color::Blue;
};