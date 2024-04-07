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
    int i = 0;
    for (auto part : parts_) {
        part->Enter();
        auto &sprite = sprites_.at(i);
        part->ApplyTo(*sprite);
        sprite->setPosition(body_.position_);
        sprite->setRotation(body_.rotation_);
        hitBoxes_.at(i) = sprite->getGlobalBounds();
#ifdef _DEBUG
        hitSprites_.at(i)->setPosition(hitBoxes_.at(i).left, hitBoxes_.at(i).top);
        hitSprites_.at(i)->setSize({hitBoxes_.at(i).width, hitBoxes_.at(i).height});
#endif  // _DEBUG
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
        hitBoxes_.at(i) = sprite->getGlobalBounds();
#ifdef _DEBUG
        hitSprites_.at(i)->setPosition(hitBoxes_.at(i).left, hitBoxes_.at(i).top);
        hitSprites_.at(i)->setSize({hitBoxes_.at(i).width, hitBoxes_.at(i).height});
#endif  // _DEBUG
        i++;
    }
#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif  // _DEBUG
}

void Shape::RegisterPart(std::shared_ptr<BasicShapePart> part)
{
    parts_.push_back(part);
    sprites_.push_back(std::make_shared<Graphic::Sprite>());
    hitBoxes_.push_back(sf::FloatRect());
#ifdef _DEBUG
    auto hitSprite = std::make_shared<Graphic::RectangleShape>();
    hitSprite->setFillColor(sf::Color::Transparent);
    hitSprite->setOutlineColor(sf::Color::Red);
    hitSprite->setOutlineThickness(1.0f);
    hitSprites_.push_back(hitSprite);
#endif  // _DEBUG
}

void Shape::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
#ifdef _DEBUG
    int i = 0;
#endif  // _DEBUG
    for (auto &sprite : sprites_) {
        renderTarget.draw(*sprite);
#ifdef _DEBUG
        auto hitSprite = hitSprites_.at(i);
        renderTarget.draw(*hitSprite);
        i++;
#endif  // _DEBUG
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

bool Shape::Intersect(const Shape &otherShape) const
{
    bool intersect = false;

    for (auto &thisBox : hitBoxes_) {
        for (auto &otherBox : otherShape.hitBoxes_) {
            intersect |= thisBox.intersects(otherBox);
        }
    }

    return intersect;
}

}  // namespace Entity

}  // namespace FA
