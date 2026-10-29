#pragma once

#include <string>

#include "Vector.h"
#include "Color.h"

struct SDL_Renderer;
struct TTF_Font;
struct TTF_TextEngine;

struct Geometry
{
    Color color = Color::White;
    bool filled = false;

    virtual ~Geometry() = default;
    virtual void Draw(SDL_Renderer* renderer) const = 0;
};

struct Rectangle : public Geometry
{
    Vector2f position;
    Vector2f size;

    void Draw(SDL_Renderer* renderer) const override;
};

struct Line : public Geometry
{
    Vector2f a;
    Vector2f b;

    void Draw(SDL_Renderer* renderer) const override;
};

struct Circle : public Geometry
{
    Vector2f position;
    float radius = 0.f;

    void Draw(SDL_Renderer* renderer) const override;

private:
    void DrawUnfilled(SDL_Renderer* renderer) const;
    void DrawFilled(SDL_Renderer* renderer) const;
};

struct Text
{
    Vector2f position;
    std::string content;
    Color color = Color::White;
    float ratioX = 0.f;
    float ratioY = 0.f;

    void Draw(TTF_TextEngine* engine, TTF_Font* font) const;
};
