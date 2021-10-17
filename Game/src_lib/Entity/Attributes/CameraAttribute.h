/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicAttribute.h"

namespace FA {

namespace Entity {

class CameraAttribute : public BasicAttribute
{
public:
    CameraAttribute(EntityService *owner);

    virtual void Update(float deltaTime) override {}
};

}  // namespace Entity

}  // namespace FA
