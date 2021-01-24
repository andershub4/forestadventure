/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "EntityState.h"

namespace FA {

class EntityStateAttack : public EntityState
{
public:
    EntityStateAttack(EntityStateMachine& stateMachine, StateData& stateData);
    virtual ~EntityStateAttack();

    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "EntityStateAttack"; }
    virtual void Enter() override;

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) override;

private:
    std::unique_ptr<Animation> animation_ = nullptr;
};

}  // namespace FA
