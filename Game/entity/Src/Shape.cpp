/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include "SFML/Graphics/Color.hpp"

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
    for (auto &entry : entries_) {
        entry.part_->Enter();
        entry.part_->ApplyTo(*entry.sprite_);
        entry.sprite_->setPosition(body_.position_);
        entry.sprite_->setRotation(body_.rotation_);
        entry.hitBox_ = entry.sprite_->getGlobalBounds();
#ifdef _DEBUG
        entry.hitSprite_->setPosition(entry.hitBox_.left, entry.hitBox_.top);
        entry.hitSprite_->setSize({entry.hitBox_.width, entry.hitBox_.height});
#endif  // _DEBUG
    }
#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif
}

void Shape::Update(float deltaTime)
{
    for (auto &entry : entries_) {
        entry.part_->Update(deltaTime);
        entry.part_->ApplyTo(*entry.sprite_);
        entry.sprite_->setPosition(body_.position_);
        entry.sprite_->setRotation(body_.rotation_);
        entry.hitBox_ = entry.sprite_->getGlobalBounds();
#ifdef _DEBUG
        entry.hitSprite_->setPosition(entry.hitBox_.left, entry.hitBox_.top);
        entry.hitSprite_->setSize({entry.hitBox_.width, entry.hitBox_.height});
#endif  // _DEBUG
    }
#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif  // _DEBUG
}

void Shape::RegisterPart(std::shared_ptr<BasicShapePart> part)
{
#ifdef _DEBUG
    auto hitSprite = std::make_shared<Graphic::RectangleShape>();
    hitSprite->setFillColor(sf::Color::Transparent);
    hitSprite->setOutlineColor(sf::Color::Red);
    hitSprite->setOutlineThickness(1.0f);
    entries_.push_back({part, std::make_shared<Graphic::Sprite>(), sf::FloatRect{}, hitSprite});
#else
    entries_.push_back({part, std::make_shared<Graphic::Sprite>(), sf::FloatRect{}});
#endif  // _DEBUG
}

void Shape::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto &entry : entries_) {
        if (entry.part_->IsDrawable()) {
            renderTarget.draw(*entry.sprite_);
        }
#ifdef _DEBUG
        if (entry.part_->IsCollidable()) {
            renderTarget.draw(*entry.hitSprite_);
        }
#endif  // _DEBUG
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

bool Shape::Intersect(const Shape &otherShape) const
{
    bool intersect = false;

    for (auto &entry : entries_) {
        if (!entry.part_->IsCollidable()) break;
        for (auto &otherEntry : otherShape.entries_) {
            if (!otherEntry.part_->IsCollidable()) break;
            intersect |= entry.hitBox_.intersects(otherEntry.hitBox_);
        }
    }

    return intersect;
}

}  // namespace Entity

}  // namespace FA
