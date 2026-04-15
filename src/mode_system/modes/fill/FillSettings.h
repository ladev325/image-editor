#pragma once
#include "../../base/ISettings.h"
#include <SFML/Graphics.hpp>

struct FillSettings : public ISettings {
  void drawUI() override {
    const char *mode_list[] = {"Local", "Global"};
    ImGui::Combo("Fill mode", reinterpret_cast<int *>(&mode), mode_list, IM_ARRAYSIZE(mode_list));
    ImGui::SliderFloat("Threshold", &threshold, 0.f, 1.f, "%.2f");

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

  enum class Mode : int { Local,
                          Global };
  static inline Mode mode = Mode::Local;
  static inline sf::Color color = sf::Color::Blue;
  static inline float threshold = 0.4;
};