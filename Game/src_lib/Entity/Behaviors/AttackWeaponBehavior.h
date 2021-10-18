/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicBehavior.h"

namespace FA {

namespace Entity {

class BasicState;

class AttackWeaponBehavior : public BasicBehavior
{
public:
    AttackWeaponBehavior(EntityService *owner);

    virtual void Update(float deltaTime) override {}
    virtual FrameType GetFrameType() const override { return FrameType::AttackWeapon; }

    void Execute(BasicState &oldState);
};

}  // namespace Entity

}  // namespace FA
