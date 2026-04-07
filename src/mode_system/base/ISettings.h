#pragma once
#include <imgui.h>

class ISettings {
public:
  ISettings() = default;
  virtual ~ISettings() = default;
  virtual void drawUI() = 0;
};