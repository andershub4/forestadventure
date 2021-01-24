/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "EntityState.h"

namespace FA {

class EntityStateIdle : public EntityState
{
public:
    EntityStateIdle(EntityStateMachine& stateMachine, StateData& stateData);
    virtual ~EntityStateIdle();

    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "EntityStateIdle"; }
    virtual void Enter() override;

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) override;
    virtual void OnAttack() override;
    virtual void OnAttackWeapon() override;

private:
    std::unique_ptr<Animation> animation_ = nullptr;
};

}  // namespace FA
