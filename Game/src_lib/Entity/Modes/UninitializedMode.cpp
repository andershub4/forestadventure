/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedMode.h"

#include "Entity/StateController.h"
#include "Entity/States/UninitializedState.h"

namespace FA {

namespace Entity {

UninitializedMode::UninitializedMode(EntityService *owner)
    : BasicMode(owner)
{}

std::unique_ptr<BasicState> UninitializedMode::CreateState(StateController &stateController,
                                                           std::shared_ptr<BasicEvent> event) const
{
    return stateController.CreateState<UninitializedState>(event);
}

}  // namespace Entity

}  // namespace FA
