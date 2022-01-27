/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicMode.h"

namespace FA {

namespace Entity {

class UninitializedMode : public BasicMode
{
public:
    UninitializedMode(EntityService& entityService, ModeController& modeController);

    virtual void Update(float deltaTime) override {}
    virtual ModeType GetModeType() const override { return ModeType::Uninitialized; }
};

}  // namespace Entity

}  // namespace FA
