#pragma once
#include <SFML/Graphics.hpp>

enum class PencilMode { KeepAlpha, IncreaseAlpha };
struct PencilConfig {
    sf::Color color = sf::Color::Red;
    PencilMode mode = PencilMode::KeepAlpha;
};