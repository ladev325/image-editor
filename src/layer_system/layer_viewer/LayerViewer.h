#pragma once
#include "../layer_container/LayerContainer.h"
#include "../../mode_system/mode_system.h"

class LayerViewer : public LayerContainer {
private:
  sf::RectangleShape frame;
  float linear_scale;
  float scale;
  sf::Vector2f position;
  sf::Vector2f prev_mouse_pos;
  bool mouse_down = false;
  sf::RenderTexture zoomed_rect_texture;
  sf::Sprite zoomed_rect_sprite;
  std::unique_ptr<Mode> mode;

  void clampPosition();
  sf::Vector2f mouseToTexturePos(sf::Vector2f mouse_coords) const;
  void onMouseDown(sf::Vector2f mouse_pos);
  void onMouseUp(sf::Vector2f mouse_pos);
  void onMouseDrag(sf::Vector2f mouse_pos);
  void onMouseWheel(float delta, sf::Vector2f mouse_pos);

public:
  LayerViewer();
  LayerViewer(sf::Vector2u size, sf::Vector2f position, sf::Vector2f frame_size,
              float outline_thickness = 2, sf::Color outline_color = sf::Color::White);
  void setSize(sf::Vector2u size) override;

  void setPosition(sf::Vector2f position);
  sf::Vector2f getPosition() const;
  void setFrameSize(sf::Vector2f frame_size);
  sf::Vector2f getFrameSize() const;

  void setOutlineThickness(float thickness);
  float getOutlineThickness() const;
  void setOutlineColor(sf::Color color);
  sf::Color getOutlineColor() const;

  void LAYER_TEST();
  void render(sf::RenderWindow &window);
  bool tick(sf::Event event, sf::RenderWindow &window);
};