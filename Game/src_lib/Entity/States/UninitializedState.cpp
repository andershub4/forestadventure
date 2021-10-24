/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/UninitializedMode.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData, EntityService& entityService)
    : BasicState(stateMachine, stateData, entityService)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::Create(const PropertyData& data)
{
    GetMode<UninitializedMode>()->Create(data);
}

void UninitializedState::OnInit()
{
    InitProperties();

    GetMode<IdleMode>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
