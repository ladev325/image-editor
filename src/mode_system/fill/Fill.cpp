#include "Fill.h"
#include "constants.h"

Fill::Fill()
    : Moded(FillMode::Global),
      Shadered(Constants::Path::FillShader),
      Colored(sf::Color::Blue),
      Thresholded(0.1) {}

bool Fill::onMouseDown(sf::RenderTexture &render_texture,
                       sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  sf::Vector2u size = render_texture.getSize();
  sf::Color new_color = getColor();
  float threshold = getThreshold();

  if (getMode() == FillMode::Local) {
    // prepare image
    sf::Vector2u texture_pos_i = sf::Vector2u(texture_pos);
    sf::Image image = render_texture.getTexture().copyToImage();
    sf::Color prev_color = image.getPixel(texture_pos_i);

    image.setPixel(texture_pos_i, new_color);
    uint8_t *pixels = (uint8_t *)image.getPixelsPtr();

    // prepare loop
    int threshold_sq = (int)(threshold * threshold * 260100.f);
    sf::Vector2i dir[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    std::vector<sf::Vector2u> q;
    q.reserve(size.x * size.y);
    q.push_back(texture_pos_i);
    std::vector<uint8_t> visited(size.x * size.y, 0);

    // loop
    for (size_t i = 0; i < q.size(); i++) {
      sf::Vector2u front = q[i];

      for (const sf::Vector2i &it : dir) {
        sf::Vector2i pos_i = sf::Vector2i(front) + it;
        if (pos_i.x >= 0 && pos_i.x < (int)size.x &&
            pos_i.y >= 0 && pos_i.y < (int)size.y) {
          unsigned int start_byte = pos_i.y * size.x + pos_i.x;
          unsigned int start_pixel = start_byte * 4;

          if (!visited[start_byte]) {
            visited[start_byte] = 1;
            int dr = pixels[start_pixel] - prev_color.r;
            int dg = pixels[start_pixel + 1] - prev_color.g;
            int db = pixels[start_pixel + 2] - prev_color.b;
            int da = pixels[start_pixel + 3] - prev_color.a;

            if (dr * dr + dg * dg + db * db + da * da < threshold_sq) {
              pixels[start_pixel] = new_color.r;
              pixels[start_pixel + 1] = new_color.g;
              pixels[start_pixel + 2] = new_color.b;
              pixels[start_pixel + 3] = new_color.a;
              q.push_back(sf::Vector2u(pos_i));
            }
          }
        }
      }
    }

    // copy image back to render_texture
    sf::Texture texture(image);
    render_texture.clear(sf::Color::Transparent);
    render_texture.draw(sf::Sprite(texture));
  }

  else {
    float threshold_sq = threshold * threshold * 4.f;
    buffer_texture.draw(sf::Sprite(render_texture.getTexture()));
    sf::Shader *shader = getShader();
    shader->setUniform("resolution", sf::Vector2f(size));
    shader->setUniform("click_pos", texture_pos);
    shader->setUniform("color", sf::Glsl::Vec4(new_color));
    shader->setUniform("threshold_sq", threshold_sq);
    render_texture.draw(buffer_sprite, shader);
  }

  render_texture.display();
  return true;
}

bool Fill::onMouseUp(sf::RenderTexture &render_texture,
                     sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  return false;
}

bool Fill::onMouseMove(sf::RenderTexture &render_texture,
                       sf::Vector2f mouse_pos, sf::Vector2f texture_pos) {
  return false;
}