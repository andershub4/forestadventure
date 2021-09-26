/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicComponent.h"

namespace FA {

namespace Entity {

class BasicState;

class AttackWeaponComponent : public BasicComponent
{
public:
    AttackWeaponComponent(ComponentHandler *owner);

    virtual void Update(float deltaTime) override {}

    void Execute(BasicState &oldState);
};

}  // namespace Entity

}  // namespace FA
