/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "Entity/EntityService.h"
#include "Entity/Shape.h"

namespace FA {

namespace Entity {

IdleState::IdleState(EntityService& entityService, StateMachine& stateMachine)
    : BasicState(entityService, stateMachine)
{}

void IdleState::Enter(std::shared_ptr<BasicEvent> event)
{
    shape_->SetAnimation(GetAnimation());
    shape_->SetImage(GetImage());
}

void IdleState::Register()
{
    shape_ = Service().GetShape();
}

void IdleState::Update(float deltaTime)
{
    shape_->Update(deltaTime);
    BasicUpdate();
}

}  // namespace Entity

}  // namespace FA
