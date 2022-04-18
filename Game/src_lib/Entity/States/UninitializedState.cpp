/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(EntityService& entityService, StateMachine& stateMachine)
    : BasicState(entityService, stateMachine)
{}

}  // namespace Entity

}  // namespace FA
