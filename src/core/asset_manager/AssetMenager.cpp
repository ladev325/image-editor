#include "AssetManager.h"

template <>
std::map<std::string, std::unique_ptr<sf::Texture>> &AssetManager::getMap() {
  return textures;
}

template <>
std::map<std::string, std::unique_ptr<sf::Shader>> &AssetManager::getMap() {
  return shaders;
}

void AssetManager::setRoot(std::string root) {
  AssetManager::root = root;
}

std::string AssetManager::getRoot() {
  return root;
}