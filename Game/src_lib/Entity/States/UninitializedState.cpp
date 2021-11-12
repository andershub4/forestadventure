/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateController& stateController, StateData& stateData,
                                       EntityService& entityService, std::shared_ptr<BasicEvent> event)
    : BasicState(stateController, stateData, entityService)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::OnInit()
{
    BasicState::Start();
}

}  // namespace Entity

}  // namespace FA
