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

    std::unique_ptr<Configuration> Build();

private:
    std::unique_ptr<Configuration> configuration_;
};

}  // namespace Entity

}  // namespace FA
