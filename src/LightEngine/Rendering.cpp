#include "Rendering.h"

#include "Utils.h"

#include <cmath>
#include <cassert>
#include <SDL3/SDL_render.h>
#include <SDL_ttf.h>

void Rectangle::Draw(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { position.x, position.y, size.x, size.y };

    if (filled)
        SDL_RenderFillRect(renderer, &rect);
    else
        SDL_RenderRect(renderer, &rect);
}

void Line::Draw(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
}

void Circle::Draw(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (radius <= 0.f)
        return;

    if (filled)
        DrawFilled(renderer);
    else
        DrawUnfilled(renderer);
}

void Circle::DrawFilled(SDL_Renderer* renderer) const
{
    const Vector2f center = position + radius;
    const int rows = static_cast<int>(std::ceil(radius));

    for (int y = -rows; y <= rows; ++y)
    {
        const float offsetY = static_cast<float>(y);
        const float widthSquared = radius * radius - offsetY * offsetY;
        if (widthSquared < 0.f)
            continue;

        const float halfWidth = std::sqrt(widthSquared);
        SDL_RenderLine(renderer, center.x - halfWidth, center.y + offsetY,
            center.x + halfWidth, center.y + offsetY);
    }
}

void Circle::DrawUnfilled(SDL_Renderer* renderer) const
{
    const Vector2f center = position + radius;

    constexpr int segments = 64;
    SDL_FPoint points[segments + 1];

    for (int i = 0; i <= segments; ++i)
    {
        const float angle = static_cast<float>(i) * 2.0f * PI / segments;

        points[i].x = center.x + std::cos(angle) * radius;
        points[i].y = center.y + std::sin(angle) * radius;
    }

    SDL_RenderLines(renderer, points, segments + 1);
}

void Text::Draw(TTF_TextEngine* engine, TTF_Font* font) const
{
    assert(engine != nullptr);
    assert(font != nullptr);

    TTF_Text* text = TTF_CreateText(engine, font, content.c_str(), content.size());
    assert(text != nullptr);

    bool success = TTF_SetTextColor(text, color.r, color.g, color.b, color.a);
    assert(success);

    int width = 0;
    int height = 0;
    success = TTF_GetTextSize(text, &width, &height);
    assert(success);

    float x = position.x - width * ratioX;
    float y = position.y - height * ratioY;
    success = TTF_DrawRendererText(text, x, y);
    assert(success);

    TTF_DestroyText(text);
}
