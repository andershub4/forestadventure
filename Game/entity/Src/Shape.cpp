/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include "SFML/Graphics/Color.hpp"

#include "Body.h"
#include "RectangleShape.h"
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
    for (auto &entry : shapeParts_) {
        entry.part_->Enter();
        entry.part_->ApplyTo(*entry.sprite_);
        entry.sprite_->setPosition(body_.position_);
        entry.sprite_->setRotation(body_.rotation_);
    }

    for (auto &entry : colliderParts_) {
        entry.part_->Enter();
        entry.part_->ApplyTo(*entry.hitRect_);
        entry.hitRect_->setPosition(body_.position_);
        entry.hitRect_->setRotation(body_.rotation_);
    }

#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif
}

void Shape::Update(float deltaTime)
{
    for (auto &entry : shapeParts_) {
        entry.part_->Update(deltaTime);
        entry.part_->ApplyTo(*entry.sprite_);
        entry.sprite_->setPosition(body_.position_);
        entry.sprite_->setRotation(body_.rotation_);
    }

    for (auto &entry : colliderParts_) {
        entry.part_->Update(deltaTime);
        entry.part_->ApplyTo(*entry.hitRect_);
        entry.hitRect_->setPosition(body_.position_);
        entry.hitRect_->setRotation(body_.rotation_);
    }

#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif  // _DEBUG
}

void Shape::RegisterShapePart(std::shared_ptr<BasicShapePart> part)
{
    shapeParts_.push_back({part, std::make_shared<Graphic::Sprite>()});
}

void Shape::RegisterColliderPart(std::shared_ptr<BasicColliderPart> part)
{
    auto hitSprite = std::make_shared<Graphic::RectangleShape>();
    hitSprite->setFillColor(sf::Color::Transparent);
    hitSprite->setOutlineColor(sf::Color::Red);
    hitSprite->setOutlineThickness(1.0f);
    colliderParts_.push_back({part, hitSprite});
}

void Shape::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto &entry : shapeParts_) {
        renderTarget.draw(*entry.sprite_);
    }

#ifdef _DEBUG
    for (auto &entry : colliderParts_) {
        auto rectShape = entry.hitRect_;
        renderTarget.draw(*rectShape);
    }
#endif  // _DEBUG

#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

bool Shape::Intersect(const Shape &otherShape) const
{
    bool intersect = false;

    for (auto &entry : colliderParts_) {
        for (auto &otherEntry : otherShape.colliderParts_) {
            intersect |= entry.hitRect_->getGlobalBounds().intersects(otherEntry.hitRect_->getGlobalBounds());
        }
    }

    return intersect;
}

}  // namespace Entity

}  // namespace FA
