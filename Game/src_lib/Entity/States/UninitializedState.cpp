/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "IdleState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData,
                                       ComponentHandler& componentHandler)
    : BasicState(stateMachine, stateData, componentHandler)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::OnInitStateData(const AnimationDb& animationDb)
{
    InitComponents(animationDb);

    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
