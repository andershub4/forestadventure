/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackBehavior.h"

#include "Entity/States/AttackState.h"

namespace FA {

namespace Entity {

AttackBehavior::AttackBehavior(PropertyHandler *owner)
    : BasicBehavior(owner)
{}

void AttackBehavior::Execute(BasicState &oldState)
{
    oldState.SwitchState<AttackState>();
}

}  // namespace Entity

}  // namespace FA
