#pragma once

#include <vector>
#include <string>
#include "Rendering.h"
#include "Color.h"

class GameManager;
struct TTF_Font;
struct TTF_TextEngine;

class Debug
{
    Debug() = delete;

    inline static std::vector<Line> mLines;
    inline static std::vector<Rectangle> mRectangles;
    inline static std::vector<Circle> mCircles;
    inline static std::vector<Text> mTexts;

    static void Draw(SDL_Renderer* renderer, TTF_TextEngine* textEngine, TTF_Font* font);

public:
    static void DrawLine(Vector2f a, Vector2f b, const Color& color);
    static void DrawRectangle(Vector2f center, Vector2f size, const Color& color, bool filled);
    static void DrawCircle(Vector2f center, float radius, const Color& color, bool filled);
    static void DrawText(Vector2f position, const std::string& text, const Color& color = Color::White,
        float ratioX = 0.f, float ratioY = 0.f);

    friend class GameManager;
};
