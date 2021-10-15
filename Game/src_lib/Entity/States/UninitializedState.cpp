/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/UninitializedBehavior.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData,
                                       PropertyHandler& propertyHandler)
    : BasicState(stateMachine, stateData, propertyHandler)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::Create(const PropertyData& data)
{
    GetBehavior<UninitializedBehavior>()->Create(data);
}

void UninitializedState::OnInitStateData(const AnimationDb& animationDb)
{
    InitProperties(animationDb);

    GetBehavior<IdleBehavior>()->Execute(*this);
}

}  // namespace Entity

}  // namespace FA
