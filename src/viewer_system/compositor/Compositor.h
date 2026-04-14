#pragma once
#include "../layer/Layer.h"
#include <list>

class Compositor {
private:
  std::list<Layer> layers;
  mutable std::list<Layer>::iterator active_layer;
  sf::RenderTexture texture_full;
  sf::RenderTexture texture_bottom;
  sf::RenderTexture texture_top;
  sf::Sprite sprite_bottom;
  sf::Sprite sprite_top;
  void bufferChanges();

public:
  Compositor();
  Compositor(sf::Vector2u size);
  void setSize(sf::Vector2u size);
  sf::Vector2u getSize() const;
  void addLayer();
  void removeLayer(int index);
  void setActiveLayer(int index);
  int getActiveLayerIndex() const;
  int getLayerCount() const;
  void display();
  sf::RenderTexture &getActiveTexture();
  const sf::RenderTexture &getOutputTexture() const; 
};