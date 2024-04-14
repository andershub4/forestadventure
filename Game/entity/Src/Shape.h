/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "SFML/Graphics/Rect.hpp"

#ifdef _DEBUG
#include "RectangleShape.h"
#endif

#include "ShapeParts/BasicShapePart.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;
class SpriteIf;

}  // namespace Graphic

namespace Entity {

struct Body;

class Shape
{
public:
    Shape(Body &body);
    ~Shape();

    void RegisterPart(std::shared_ptr<BasicShapePart> part);
    void Enter();
    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf &renderTarget) const;
    bool Intersect(const Shape &shape) const;

private:
    struct Entry
    {
        std::shared_ptr<BasicShapePart> part_;
        std::shared_ptr<Graphic::SpriteIf> sprite_{};
        sf::FloatRect hitBox_{};
#ifdef _DEBUG
        std::shared_ptr<Graphic::RectangleShape> hitSprite_{};
#endif  // _DEBUG
    };

private:
    std::vector<Entry> entries_;
    Body &body_;
#ifdef _DEBUG
    Graphic::RectangleShape rShape_;
#endif  // _DEBUG
};

}  // namespace Entity

}  // namespace FA
