/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "BasicMode.h"

namespace FA {

namespace Entity {

class BasicState;

class IdleMode : public BasicMode
{
public:
    IdleMode(EntityService *owner);

    virtual void Update(float deltaTime) override {}
    virtual FrameType GetFrameType() const override { return FrameType::Idle; }

    void Execute(BasicState &oldState);
};

}  // namespace Entity

}  // namespace FA
