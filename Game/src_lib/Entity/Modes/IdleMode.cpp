/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleMode.h"

#include "Entity/States/IdleState.h"
#include "Entity/StateController.h"
#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

IdleMode::IdleMode(EntityService *owner)
    : BasicMode(owner)
{}

void IdleMode::Enter(std::shared_ptr<BasicEvent> event)
{
    Owner()->GetShape()->Set(FrameType::Idle);
}

std::unique_ptr<BasicState> IdleMode::CreateState(StateController &stateController, std::shared_ptr<BasicEvent> event) const
{
    return stateController.CreateState<IdleState>(event);
}

}  // namespace Entity

}  // namespace FA
