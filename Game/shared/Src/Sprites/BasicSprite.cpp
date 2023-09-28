/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/BasicSprite.h"

#include <SFML/Graphics/Rect.hpp>

#include "IRenderTarget.h"
#include "Sprite.h"

namespace FA {

namespace Shared {

BasicSprite::BasicSprite(std::shared_ptr<Graphic::ISprite> sprite)
    : sprite_(sprite)
{}

void BasicSprite::Update(float deltaTime)
{}

void BasicSprite::SetPosition(const sf::Vector2f& position)
{
    sprite_->setPosition(position);
}

void BasicSprite::SetRotation(float rot)
{
    sprite_->setRotation(rot);
}

void BasicSprite::DrawTo(Graphic::IRenderTarget& renderTarget) const
{
    renderTarget.draw(*sprite_);
}

void BasicSprite::Center()
{
    sprite_->setOrigin(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
}

}  // namespace Shared

}  // namespace FA
