/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Body.h"

namespace FA {

namespace Entity {

Shape::Shape(Body& body)
    : body_(body)
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

void Shape::Enter()
{
    for (auto sprite : sprites_) {
        sprite->SetPosition(body_.position_);
        sprite->SetRotation(body_.rotation_);
        sprite->Enter();
    }
}

void Shape::Update(float deltaTime)
{
    for (auto sprite : sprites_) {
        sprite->SetPosition(body_.position_);
        sprite->SetRotation(body_.rotation_);
        sprite->Update(deltaTime);
    }
}

void Shape::RegisterSprite(std::shared_ptr<BasicSprite> sprite)
{
    sprites_.push_back(sprite);
}

void Shape::DrawTo(sf::RenderTarget& renderTarget)
{
    for (auto sprite : sprites_) {
        sprite->DrawTo(renderTarget);
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

}  // namespace Entity

}  // namespace FA
