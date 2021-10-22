/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleBehavior.h"

#include "Entity/States/IdleState.h"

namespace FA {

namespace Entity {

IdleBehavior::IdleBehavior(EntityService *owner)
    : BasicBehavior(owner)
{}

void IdleBehavior::Execute(BasicState &oldState)
{
    oldState.SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA