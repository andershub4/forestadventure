/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackMode.h"

#include "Entity/States/AttackState.h"
#include "Entity/StateController.h"
#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

AttackMode::AttackMode(EntityService *owner)
    : BasicMode(owner)
{}

void AttackMode::Enter(std::shared_ptr<BasicEvent> event)
{
    Owner()->GetShape()->Set(FrameType::Attack);
}

std::unique_ptr<BasicState> AttackMode::CreateState(StateController &stateController, std::shared_ptr<BasicEvent> event) const
{
    return stateController.CreateState<AttackState>(event);
}

}  // namespace Entity

}  // namespace FA
