#include "ModeSelector.h"

ModeSelector::ModeSelector(std::unique_ptr<IMode> &mode)
    : mode(mode) {}

bool ModeSelector::drawUI() {
  bool changed = false;

  auto ModeButton = [&](const char *label, auto mode_type) {
    using T = std::remove_pointer_t<decltype(mode_type)>;
    bool isActive = dynamic_cast<T *>(mode.get()) != nullptr;
    if (isActive) {
      ImVec4 color = ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered);
      ImGui::PushStyleColor(ImGuiCol_Button, color);
    }
    if (ImGui::Button(label)) {
      mode = std::make_unique<T>();
      changed = true;
    }
    if (isActive)
      ImGui::PopStyleColor();
  };

  ModeButton("Pencil", (PencilMode *)0);
  ModeButton("Fill", (FillMode *)0);
  ModeButton("Brush", (BrushMode *)0);
  return changed;
}