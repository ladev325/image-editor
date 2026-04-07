#pragma once
#include "../compositor/Compositor.h"
#include "../../mode_system/mode_system.h" // IWYU pragma: export

class Viewport {
private:
  Compositor compositor;
  sf::RectangleShape frame;
  float linear_scale;
  float scale;
  sf::Vector2f position;
  sf::Vector2f prev_mouse_pos;
  bool mouse_down = false;
  sf::RenderTexture zoomed_rect_texture;
  sf::Sprite zoomed_rect_sprite;
  std::unique_ptr<IMode> mode;

  // render
  void renderViewer(sf::RenderWindow &window);
  void renderUI();
  void clampPosition();
  sf::Vector2f mouseToTexturePos(sf::Vector2f mouse_coords) const;

  // tick
  void onMouseDown(sf::Vector2f mouse_pos);
  void onMouseUp(sf::Vector2f mouse_pos);
  void onMouseDrag(sf::Vector2f mouse_pos);
  void onMouseWheel(float delta, sf::Vector2f mouse_pos);

public:
  Viewport();
  Viewport(sf::Vector2u size, sf::Vector2f position, sf::Vector2f frame_size,
           float outline_thickness = 2, sf::Color outline_color = sf::Color::White);
  void render(sf::RenderWindow &window);
  void tick(const sf::Event &event, sf::RenderWindow &window);
  void setSize(sf::Vector2u size);

  void setPosition(sf::Vector2f position);
  sf::Vector2f getPosition() const;
  void setFrameSize(sf::Vector2f frame_size);
  sf::Vector2f getFrameSize() const;

  void setOutlineThickness(float thickness);
  float getOutlineThickness() const;
  void setOutlineColor(sf::Color color);
  sf::Color getOutlineColor() const;

  void LAYER_TEST();
};