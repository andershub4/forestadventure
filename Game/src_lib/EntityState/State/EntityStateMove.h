/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "EntityState.h"
#include "Movement/Movement.h"

namespace FA {

class EntityStateMove : public EntityState
{
public:
    EntityStateMove(EntityStateMachine& stateMachine, StateData& stateData);
    virtual ~EntityStateMove();

    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "EntityStateMove"; }
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void OnStopMove() override;

private:
    std::unique_ptr<Animation> animation_ = nullptr;
    Movement movement_;
};

}  // namespace FA
