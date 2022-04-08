/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shape.h"

namespace FA {

namespace Entity {

AttackMode::AttackMode(EntityService& entityService, ModeController& modeController)
    : BasicMode(entityService, modeController)
{}

void AttackMode::Enter(std::shared_ptr<BasicEvent> event)
{
    shape_->SetAnimation(GetAnimation());
    shape_->SetImage(GetImage());
}

void AttackMode::Register()
{
    shape_ = Service().GetShape();
}

void AttackMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);
    BasicUpdate();
}

}  // namespace Entity

}  // namespace FA
