/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class UninitializedState : public BasicState
{
public:
    UninitializedState(EntityService& entityService, StateMachine& stateMachine);

    virtual void Update(float deltaTime) override {}
    virtual StateType GetStateType() const override { return StateType::Uninitialized; }
};

}  // namespace Entity

}  // namespace FA
