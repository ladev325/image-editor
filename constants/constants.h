#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace Constants {
    namespace Path {
        inline const std::string ShapeAA = "shaders/shape_aa.frag";
    }

    namespace Viewer {
        inline constexpr float ScaleLinearMin = 0.8f;
        inline constexpr float ScaleLinearMax = 2.f;
        inline constexpr float ScaleSpeed = 0.02f;
        inline constexpr float ScalePow = 10.f;
        
        inline const sf::Color BgColor{30, 30, 30};
        inline const sf::Color InnerFrameColor{170, 170, 170};
        inline constexpr int InnerFrameThickness = 4;
    }

    namespace ShapeAA {
        inline constexpr int Radius = 1;
        inline constexpr float TightCoef = 0.15f;
    }
}