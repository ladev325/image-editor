#pragma once
#include "../../mode_system/mode_system.h"  // IWYU pragma: export

class ModeSelector {
private:
  std::unique_ptr<IMode>& mode;

public:
  ModeSelector(std::unique_ptr<IMode>& mode);
  bool drawUI();
};