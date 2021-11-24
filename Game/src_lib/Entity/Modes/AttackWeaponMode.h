/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicMode.h"

namespace FA {

namespace Entity {

class AttackWeaponMode : public BasicMode
{
public:
    AttackWeaponMode(EntityService &entityService);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;

    virtual void Update(float deltaTime) override;
    virtual FrameType GetFrameType() const override { return FrameType::AttackWeapon; }
    virtual ModeType GetModeType() const override { return ModeType::AttackWeapon; }
};

}  // namespace Entity

}  // namespace FA
