/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Entity {

class BasicComponent
{
public:
    virtual ~BasicComponent() = default;

    virtual void Update(float deltaTime) = 0;
};

}  // namespace Entity

}  // namespace FA
