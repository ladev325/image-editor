#include "LayerContainer.h"
#include <stdexcept>

LayerContainer::LayerContainer() : LayerContainer({300, 300}) {}
LayerContainer::LayerContainer(sf::Vector2u size)
    : texture_full(size),
      texture_bottom(size), sprite_bottom(texture_bottom.getTexture()),
      texture_top(size), sprite_top(texture_top.getTexture()) {
  layers.emplace_back(getSize());
  active_layer = layers.begin();

  texture_full.clear(sf::Color::Transparent);
  texture_bottom.clear(sf::Color::Transparent);
  texture_top.clear(sf::Color::Transparent);
  texture_full.display();
  texture_bottom.display();
  texture_top.display();
}

// ---------PRIVATE---------

void LayerContainer::bufferChanges() {
  sf::Vector2u resolution = getSize();

  // assemble bottom
  if (std::distance(layers.begin(), active_layer) < 2) {
    (void)texture_bottom.resize({1, 1});
  }

  else {
    if (texture_bottom.getSize() != resolution) {
      if (texture_bottom.resize(resolution)) {
        sprite_bottom.setTexture(texture_bottom.getTexture(), true);
      }
    }
    texture_bottom.clear(sf::Color::Transparent);
    for (auto it = layers.begin(); it != active_layer; it++) {
      const sf::Sprite &sprite = it->getSprite();
      texture_bottom.draw(sprite);
    }
    texture_bottom.display();
  }

  // assemble top
  if (std::distance(active_layer, layers.end()) < 3) {
    (void)texture_top.resize({1, 1});
  }

  else {
    if (texture_top.getSize() != resolution) {
      if (texture_top.resize(resolution)) {
        sprite_top.setTexture(texture_top.getTexture(), true);
      }
    }
    texture_top.clear(sf::Color::Transparent);
    for (auto it = std::next(active_layer); it != layers.end(); it++) {
      const sf::Sprite &sprite = it->getSprite();
      texture_top.draw(sprite);
    }
    texture_top.display();
  }
}

// ---------PUBLIC SIZE---------

void LayerContainer::setSize(sf::Vector2u size) {
  (void)texture_full.resize(size);
  for (auto &layer : layers) {
    layer.setSize(size);
  }
  bufferChanges();
}

sf::Vector2u LayerContainer::getSize() const {
  return texture_full.getSize();
}

// ---------PUBLIC LAYERS---------

void LayerContainer::addLayer() {
  layers.emplace_back(getSize());
  bufferChanges();
}

void LayerContainer::removeLayer(int index) {
  // validate input
  if (index < 0 || index >= layers.size()) {
    throw std::invalid_argument("Layer index is out of range");
  }
  if (layers.size() <= 1) {
    throw std::runtime_error("The last layer can't be deleted");
  }

  // correct active layer
  auto it = std::next(layers.begin(), index);
  if (it == active_layer) {
    auto next = std::next(it);
    if (next == layers.end()) {
      active_layer = std::prev(it);
    }
    else {
      active_layer = next;
    }
  }

  layers.erase(it);
  bufferChanges();
}

void LayerContainer::setActiveLayer(int index) {
  if (index < 0 || index >= layers.size()) {
    throw std::invalid_argument("Layer index is out of range");
  }
  active_layer = std::next(layers.begin(), index);
  bufferChanges();
}

int LayerContainer::getActiveLayerIndex() const {
  auto const_it = std::list<Layer>::const_iterator(active_layer);
  return std::distance(layers.begin(), const_it);
}

int LayerContainer::getLayerCount() const {
  return layers.size();
}

void LayerContainer::display() {
  texture_full.clear(sf::Color::Transparent);

  // draw bottom
  if (texture_bottom.getSize() == sf::Vector2u(1, 1)) {
    if (active_layer != layers.begin()) {
      texture_full.draw(layers.begin()->getSprite());
    }
  }
  else {
    texture_full.draw(sprite_bottom);
  }

  // draw active
  texture_full.draw(active_layer->getSprite());

  // draw top
  if (texture_top.getSize() == sf::Vector2u(1, 1)) {
    if (active_layer != std::prev(layers.end())) {
      texture_full.draw(std::prev(layers.end())->getSprite());
    }
  }
  else {
    texture_full.draw(sprite_top);
  }

  texture_full.display();
}

// ---------PROTECTED---------

sf::RenderTexture &LayerContainer::getActiveTexture() {
  return active_layer->getRenderTexture();
}

const sf::RenderTexture &LayerContainer::getFullTexture() const {
  return texture_full;
}