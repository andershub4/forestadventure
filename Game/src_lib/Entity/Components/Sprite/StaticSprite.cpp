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

StaticSprite::StaticSprite(unsigned int size, const sf::Vector2u &position, const sf::Texture *texture,
                           const sf::IntRect &rect)
    : BasicSprite(size)
{
    rectShape_.setPosition(static_cast<sf::Vector2f>(position));
    rectShape_.setSize({static_cast<float>(size), static_cast<float>(size)});
    rectShape_.setTexture(texture);
    rectShape_.setTextureRect(rect);
}

StaticSprite::~StaticSprite() = default;

void StaticSprite::Update(float deltaTime)
{}

void StaticSprite::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(rectShape_);
}

sf::Vector2f StaticSprite::GetPosition() const
{
    return rectShape_.getPosition();
}

void StaticSprite::Move(const Movement &movement)
{
    movement.ApplyTo(&rectShape_);
}

}  // namespace Entity

}  // namespace FA
