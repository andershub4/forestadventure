
/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/StateMachine.h"

namespace FA {

namespace Entity {

BasicState::BasicState(StateMachine& stateMachine, StateData& stateData, ComponentHandler& componentHandler)
    : stateMachine_(stateMachine)
    , stateData_(stateData)
    , componentHandler_(componentHandler)
{}

BasicState::~BasicState() = default;

void BasicState::SwitchState(std::unique_ptr<BasicState> newState)
{
    stateMachine_.SetState(std::move(newState));
}

void BasicState::Awake()
{
    componentHandler_.Awake();
}

void BasicState::InitComponents(const AnimationDb& animationDb)
{
    componentHandler_.InitComponents(animationDb);
}

}  // namespace Entity

}  // namespace FA
