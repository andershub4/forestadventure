/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleMode.h"

#include "Entity/States/IdleState.h"

namespace FA {

namespace Entity {

IdleMode::IdleMode(EntityService *owner)
    : BasicMode(owner)
{}

void IdleMode::Execute(BasicState &oldState)
{
    oldState.SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
