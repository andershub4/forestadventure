/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/EntityService.h"
#include "Entity/Shape.h"

namespace FA {

namespace Entity {

AttackState::AttackState(EntityService& entityService, StateMachine& stateMachine)
    : BasicState(entityService, stateMachine)
{}

void AttackState::Enter(std::shared_ptr<BasicEvent> event)
{
    shape_->SetAnimation(GetAnimation());
    shape_->SetImage(GetImage());
}

void AttackState::Register()
{
    shape_ = Service().GetShape();
}

void AttackState::Update(float deltaTime)
{
    shape_->Update(deltaTime);
    BasicUpdate();
}

}  // namespace Entity

}  // namespace FA
