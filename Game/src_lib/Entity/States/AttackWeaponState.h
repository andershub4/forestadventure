/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class AttackWeaponState : public BasicState
{
public:
    AttackWeaponState(StateController& stateController, StateData& stateData, EntityService& entityService,
                      std::shared_ptr<BasicEvent> event);
    virtual ~AttackWeaponState();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual std::string Name() const override { return "AttackWeaponState"; }
    virtual ModeType GetModeType() const override { return ModeType::AttackWeapon; }
};

}  // namespace Entity

}  // namespace FA
