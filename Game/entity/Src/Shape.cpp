/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include "SFML/Graphics/Rect.hpp"

#include "Body.h"
#include "RenderTargetIf.h"
#include "Sprite.h"

namespace FA {

namespace Entity {

Shape::Shape(Body &body)
    : body_(body)
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

Shape::~Shape() = default;

void Shape::Enter()
{
    int i = 0;
    for (auto part : parts_) {
        part->Enter();
        auto &sprite = sprites_.at(i);
        part->ApplyTo(*sprite);
        sprite->setPosition(body_.position_);
        sprite->setRotation(body_.rotation_);
        i++;
    }
#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif
}

void Shape::Update(float deltaTime)
{
    int i = 0;
    for (auto part : parts_) {
        part->Update(deltaTime);
        auto &sprite = sprites_.at(i);
        part->ApplyTo(*sprite);
        sprite->setPosition(body_.position_);
        sprite->setRotation(body_.rotation_);
        i++;
    }
#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif
}

void Shape::RegisterPart(std::shared_ptr<BasicShapePart> part)
{
    parts_.push_back(part);
    sprites_.push_back(std::make_shared<Graphic::Sprite>());
}

void Shape::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto &sprite : sprites_) {
        renderTarget.draw(*sprite);
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

bool Shape::Intersect(const Shape &otherShape) const
{
    bool intersect = false;

    for (auto &thisSprite : sprites_) {
        auto thisBB = thisSprite->getGlobalBounds();
        for (auto &otherSprite : otherShape.sprites_) {
            auto otherBB = otherSprite->getGlobalBounds();
            intersect |= thisBB.intersects(otherBB);
        }
    }

    return intersect;
}

}  // namespace Entity

}  // namespace FA
