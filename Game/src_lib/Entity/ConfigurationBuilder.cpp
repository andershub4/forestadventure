/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ConfigurationBuilder.h"

namespace FA {

namespace Entity {

ConfigurationBuilder::ConfigurationBuilder(const sf::Vector2f &position, float scale, FaceDirection faceDir)
    : faceDir_(faceDir)
{
    transform_ = TransformComponent(position, scale);
}

ConfigurationBuilder::~ConfigurationBuilder() = default;

void ConfigurationBuilder::AddSprite(const AnimationComponent &animation)
{
    sprite_ = SpriteComponent(transform_, animation);
}

void ConfigurationBuilder::AddMovement(float velocity)
{
    movement_ = MovementComponent(velocity);
}

Configuration ConfigurationBuilder::Build()
{
    Configuration c;
    c.faceDir_ = faceDir_;
    c.transform_ = transform_;
    c.movement_ = movement_;
    c.sprite_ = sprite_;

    return c;
}

}  // namespace Entity

}  // namespace FA
