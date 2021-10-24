/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedMode.h"

#include "Entity/States/IdleState.h"

namespace FA {

namespace Entity {

UninitializedMode::UninitializedMode(EntityService *owner)
    : BasicMode(owner)
{}

void UninitializedMode::Execute(BasicState &oldState)
{
    oldState.SwitchState<IdleState>();
}

void UninitializedMode::Create(const PropertyData &data)
{
    onCreate_(*Owner(), data);
}

}  // namespace Entity

}  // namespace FA
