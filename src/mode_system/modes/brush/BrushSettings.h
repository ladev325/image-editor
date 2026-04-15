#pragma once
#include "../../base/ISettings.h"

struct BrushSettings : public ISettings {
  void drawUI() override {
    ImGui::SliderInt("Thickness", &thickness, 1, 100);
    ImGui::Checkbox("Antialiased", &antialiased);

    float temp_color[] = {
        color.r / 255.f,
        color.g / 255.f,
        color.b / 255.f,
        color.a / 255.f};

    if (ImGui::ColorEdit4("Color", temp_color, ImGuiColorEditFlags_NoInputs)) {
      color.r = temp_color[0] * 255.f;
      color.g = temp_color[1] * 255.f;
      color.b = temp_color[2] * 255.f;
      color.a = temp_color[3] * 255.f;
    }
  }

  static inline sf::Color color = sf::Color::Blue;
  static inline int thickness = 10;
  static inline bool antialiased = true;
};