#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
  static inline std::string root = "/";
  static inline std::map<std::string, std::unique_ptr<sf::Texture>> textures;
  static inline std::map<std::string, std::unique_ptr<sf::Shader>> shaders;
  template <typename T>
  static std::map<std::string, std::unique_ptr<T>> &getMap();

public:
  static void setRoot(std::string root);
  static std::string getRoot();

  template <typename T>
  static T &get(std::string filename) {
    auto &map = getMap<T>();

    auto it = map.find(filename);
    if (it != map.end()) {
      return *it->second;
    }

    auto new_asset = std::make_unique<T>();
    bool success = false;

    if constexpr (std::is_same_v<T, sf::Shader>) {
      if (!sf::Shader::isAvailable()) {
        throw std::runtime_error("Your system does not support shaders, aborting");
      }
      success = new_asset->loadFromFile(root + filename, sf::Shader::Type::Fragment);
    }
    else {
      success = new_asset->loadFromFile(root + filename);
    }
    if (!success) {
      throw std::runtime_error("Error loading " + filename + ", aborting");
    }

    auto &ref = *new_asset;
    map[filename] = std::move(new_asset);
    return ref;
  }
};