/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "IdleState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::OnInitStateData(std::unique_ptr<Configuration> configuration)
{
    stateData_.configuration_ = std::move(configuration);

    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
