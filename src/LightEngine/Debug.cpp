#include "Debug.h"

#include <cassert>

void Debug::Draw(SDL_Renderer* renderer, TTF_TextEngine* textEngine, TTF_Font* font)
{
    for (const Line& line : mLines)
    {
        line.Draw(renderer);
    }

    mLines.clear();

    for (const Rectangle& rect : mRectangles)
    {
        rect.Draw(renderer);
    }

    mRectangles.clear();

    for (const Circle& circle : mCircles)
    {
        circle.Draw(renderer);
    }

    mCircles.clear();

    for (const Text& text : mTexts)
    {
        text.Draw(textEngine, font);
    }

    mTexts.clear();
}

void Debug::DrawLine(Vector2f a, Vector2f b, const Color& color)
{
    Line line;
    line.a = a;
    line.b = b;
    line.color = color;

    mLines.push_back(line);
}

void Debug::DrawRectangle(Vector2f center, Vector2f size, const Color& color, bool filled)
{
    Rectangle rect;

    rect.position = center - size / 2.f;
    rect.size = size;
    rect.color = color;
    rect.filled = filled;

    mRectangles.push_back(rect);
}

void Debug::DrawCircle(Vector2f center, float radius, const Color& color, bool filled)
{
    Circle circle;

    circle.position = center - radius;
    circle.radius = radius;
    circle.color = color;
    circle.filled = filled;

    mCircles.push_back(circle);
}

void Debug::DrawText(Vector2f position, const std::string& text, const Color& color, float ratioX, float ratioY)
{
    assert(ratioX >= 0.f && ratioX <= 1.f);
    assert(ratioY >= 0.f && ratioY <= 1.f);

    if (text.empty())
        return;

    mTexts.push_back({ position, text, color, ratioX, ratioY });
}
