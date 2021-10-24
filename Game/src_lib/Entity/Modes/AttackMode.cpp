/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackMode.h"

#include "Entity/States/AttackState.h"

namespace FA {

namespace Entity {

AttackMode::AttackMode(EntityService *owner)
    : BasicMode(owner)
{}

void AttackMode::Execute(BasicState &oldState)
{
    oldState.SwitchState<AttackState>();
}

}  // namespace Entity

}  // namespace FA
