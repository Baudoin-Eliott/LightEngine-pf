#include "Color.h"

Color::Color(uint8 red, uint8 green, uint8 blue, uint8 alpha)
    : r(red), g(green), b(blue), a(alpha)
{
}

const Color Color::White{ 255, 255, 255 };
const Color Color::Black{ 0, 0, 0 };
const Color Color::Red{ 255, 0, 0 };
const Color Color::Green{ 0, 255, 0 };
const Color Color::Blue{ 0, 0, 255 };
const Color Color::Yellow{ 255, 255, 0 };
const Color Color::Cyan{ 0, 255, 255 };
const Color Color::Magenta{ 255, 0, 255 };
const Color Color::Gray{ 128, 128, 128 };
const Color Color::Orange{ 255, 165, 0 };
const Color Color::Transparent{ 0, 0, 0, 0 };
