
/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityState.h"

#include "Entity/Entity.h"
#include "EntityState/EntityStateMachine.h"

namespace FA {

EntityState::EntityState(EntityStateMachine& stateMachine, Entity& entity, StateData& stateData)
    : stateMachine_(stateMachine)
    , entity_(entity)
    , stateData_(stateData)
{}

EntityState::~EntityState() = default;

void EntityState::SwitchState(std::unique_ptr<EntityState> newState)
{
    stateMachine_.SetState(std::move(newState));
}

}  // namespace FA
