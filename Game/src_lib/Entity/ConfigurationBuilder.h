/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "Configuration.h"

namespace FA {

namespace Entity {

class ConfigurationBuilder
{
public:
    ConfigurationBuilder(const sf::Vector2f &position, float scale, FaceDirection faceDir);
    ~ConfigurationBuilder();

    void AddSprite(const AnimationComponent &animation);
    void AddMovement(float velocity);

    Configuration Build();

private:
    FaceDirection faceDir_;
    TransformComponent transform_;
    MovementComponent movement_;
    SpriteComponent sprite_;
};

}  // namespace Entity

}  // namespace FA
