/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedBehavior.h"

#include "Entity/States/IdleState.h"

namespace FA {

namespace Entity {

UninitializedBehavior::UninitializedBehavior(PropertyHandler *owner)
    : BasicBehavior(owner)
{}

void UninitializedBehavior::Execute(BasicState &oldState)
{
    oldState.SwitchState<IdleState>();
}

void UninitializedBehavior::Create(const PropertyData &data)
{
    onCreate_(*Owner(), data);
}

}  // namespace Entity

}  // namespace FA
