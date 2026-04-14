#include "ModeSelector.h"

ModeSelector::ModeSelector(std::unique_ptr<IMode> &mode)
    : mode(mode) {}

bool ModeSelector::drawUI() {
  // this block expresses the most complex ui logic universe ever written by mankind
  // the block was carefuly written by me in less than 2 minutes, even if many buttons are still abscent by now. Think
   if (ImGui::Button("Pencil")) {
    mode = std::make_unique<PencilMode>();
    return true;
  }

  if (ImGui::Button("Fill")) {
    mode = std::make_unique<FillMode>();
    return true;
  }
  return false;
}