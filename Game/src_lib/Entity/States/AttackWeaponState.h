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
    AttackWeaponState(StateMachine& stateMachine, StateData& stateData, ComponentHandler& componentHandler);
    virtual ~AttackWeaponState();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual std::string Name() const override { return "AttackWeaponState"; }
    virtual void Enter() override;

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) override;
};

}  // namespace Entity

}  // namespace FA
