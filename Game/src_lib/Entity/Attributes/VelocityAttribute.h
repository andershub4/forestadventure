/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "BasicAttribute.h"

namespace FA {

namespace Entity {

class VelocityAttribute : public BasicAttribute
{
public:
    VelocityAttribute(PropertyHandler *owner);

    virtual void Update(float deltaTime) override {}

    void SetVelocity(float velocity);
    float GetVelocity() const;

private:
    float velocity_{};
};

}  // namespace Entity

}  // namespace FA
