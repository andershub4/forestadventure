
/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/StateMachine.h"

namespace FA {

namespace Entity {

BasicState::BasicState(StateMachine& stateMachine, BasicSprite& sprite, StateData& stateData)
    : stateMachine_(stateMachine)
    , sprite_(sprite)
    , stateData_(stateData)
{}

BasicState::~BasicState() = default;

void BasicState::SwitchState(std::unique_ptr<BasicState> newState)
{
    stateMachine_.SetState(std::move(newState));
}

}  // namespace Entity

}  // namespace FA
