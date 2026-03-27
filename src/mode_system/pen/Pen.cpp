// #include "Pen.h"
// #include <cmath>

// Pen::Pen()
//     : Pencil(), buffer_texture({300, 300}),
//       buffer_sprite(buffer_texture.getTexture()), thickness(10), blur(1) {
//   init();
// }

// Pen::Pen(int thickness, int blur)
//     : Pencil(), buffer_texture({300, 300}),
//       buffer_sprite(buffer_texture.getTexture()), thickness(thickness),
//       blur(blur) {
//   init();
// }

// void Pen::init() {
//   if (!sf::Shader::isAvailable()) {
//     throw std::runtime_error("Your system does not support shaders");
//   }
//   if (!shader.loadFromFile("shaders/blur.frag", sf::Shader::Type::Fragment)) {
//     throw std::runtime_error("Error loading blur.frag");
//   }
// }

// void Pen::setTextureSize(sf::Vector2u texture_size) {
//   if(buffer_texture.resize(texture_size)) {
//     buffer_sprite.setTexture(buffer_texture.getTexture(), true);
//   }
// }

// bool Pen::onMouseDown(sf::RenderTexture &render_texture,
//                          sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
//   bool state = onMouseDown(render_texture, mouse_pos, texture_pos);
//   if(!state) return false;
//   buffer_texture.clear(sf::Color::Transparent);
//   return true;
// }

// void Pen::drawPoint(sf::RenderTexture &render_texture, sf::Vector2f pos,
//                     sf::Color color) {
//   sf::CircleShape circle(thickness / 2.0f);
//   circle.setFillColor(sf::Color(0, 255, 0, 20));
//   circle.setOrigin({thickness / 2.0f, thickness / 2.0f});
//   circle.setPosition(pos);
//   buffer_texture.draw(circle);
// }

// void Pen::drawLine(sf::RenderTexture &render_texture, sf::Vector2f pos1,
//                    sf::Vector2f pos2, sf::Color color) {
//   sf::Vector2f delta = pos2 - pos1;
//   float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);

//   if (length == 0.0f) {
//     drawPoint(buffer_texture, pos1, color);
//     return;
//   }

//   float step = std::max(1.0f, thickness * 0.25f);
//   float steps = length / step;

//   for (float i = 0; i <= steps; i++) {
//     float t = i / steps;
//     sf::Vector2f pos = pos1 + delta * t;
//     drawPoint(buffer_texture, pos, color);
//   }
// }

// void Pen::updateTexture(sf::RenderTexture &render_texture) {
//   render_texture.draw(buffer_sprite);
//   render_texture.display();
// }