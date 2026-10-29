#pragma once

#include "Utils.h"

struct Color
{
    uint8 r = 255;
    uint8 g = 255;
    uint8 b = 255;
    uint8 a = 255;

    Color() = default;
    Color(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255);

    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Magenta;
    static const Color Gray;
    static const Color Orange;
    static const Color Transparent;
};
