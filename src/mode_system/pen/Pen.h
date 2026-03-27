// #pragma once
// #include "../pencil/Pencil.h"
// #include "SFML/Graphics/RenderTexture.hpp"
// #include "SFML/Graphics/Sprite.hpp"

// class Pen : public Pencil {
// private:
//   sf::RenderTexture buffer_texture;
//   sf::Sprite buffer_sprite;
//   int thickness = 10;
//   int blur = 1;
//   sf::Shader shader;
//   void init();

// public:
//   Pen();
//   Pen(int thickness, int blur = 1);
//   void setTextureSize(sf::Vector2u texture_size) override;
//   void setThickness(int thickness);
//   int getThickness(int thickness) const;

//   bool onMouseDown(sf::RenderTexture &render_texture, sf::Vector2f mouse_pos,
//                    sf::Vector2f texture_pos) override;

//   void drawPoint(sf::RenderTexture &render_texture, sf::Vector2f pos,
//                  sf::Color color) override;
//   void drawLine(sf::RenderTexture &render_texture, sf::Vector2f pos1,
//                 sf::Vector2f pos2, sf::Color color) override;
//   void updateTexture(sf::RenderTexture &render_texture) override;
// };