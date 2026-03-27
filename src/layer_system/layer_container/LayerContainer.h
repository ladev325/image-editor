#pragma once
#include "../layer/Layer.h"
#include <list>

class LayerContainer {
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
  LayerContainer();
  LayerContainer(sf::Vector2u size);
  virtual void setSize(sf::Vector2u size);
  sf::Vector2u getSize() const;
  void addLayer();
  void removeLayer(int index);
  void setActiveLayer(int index);
  int getActiveLayerIndex() const;
  int getLayerCount() const;
  void display();

protected:
  sf::RenderTexture &getActiveTexture();
  const sf::RenderTexture &getFullTexture() const;
};