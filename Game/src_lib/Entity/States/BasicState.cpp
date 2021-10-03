
/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/StateMachine.h"

namespace FA {

namespace Entity {

BasicState::BasicState(StateMachine& stateMachine, StateData& stateData, PropertyHandler& propertyHandler)
    : stateMachine_(stateMachine)
    , stateData_(stateData)
    , propertyHandler_(propertyHandler)
{}

BasicState::~BasicState() = default;

void BasicState::SwitchState(std::unique_ptr<BasicState> newState)
{
    stateMachine_.SetState(std::move(newState));
}

void BasicState::Awake()
{
    propertyHandler_.Awake();
}

void BasicState::InitProperties(const AnimationDb& animationDb)
{
    propertyHandler_.InitProperties(animationDb);
}

}  // namespace Entity

}  // namespace FA
