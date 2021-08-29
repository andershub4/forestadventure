/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TransformComponent.h"

namespace FA {

namespace Entity {

TransformComponent::TransformComponent(const sf::Vector2f &position, float scale)
    : position_(position)
    , scale_(scale)
{}

void TransformComponent::Move(const sf::Vector2f &offset)
{
    position_ = {position_.x + offset.x, position_.y + offset.y};
}

}  // namespace Entity

}  // namespace FA
