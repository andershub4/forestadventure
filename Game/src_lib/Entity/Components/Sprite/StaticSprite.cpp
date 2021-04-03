/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StaticSprite.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Movement/Movement.h"

namespace FA {

namespace Entity {

StaticSprite::StaticSprite(const sf::Vector2u &position, const sf::Texture *texture, const sf::IntRect &rect)
{
    sprite_.setPosition(static_cast<sf::Vector2f>(position));
    sprite_.setScale(2, 2);
    sprite_.setTexture(*texture);
    sprite_.setTextureRect(rect);
}

StaticSprite::~StaticSprite() = default;

void StaticSprite::Update(float deltaTime)
{}

void StaticSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

sf::Vector2f StaticSprite::GetPosition() const
{
    return sprite_.getPosition();
}

void StaticSprite::Move(const Movement &movement)
{
    movement.ApplyTo(&sprite_);
}

}  // namespace Entity

}  // namespace FA
