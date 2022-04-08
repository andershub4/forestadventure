/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shape.h"

namespace FA {

namespace Entity {

IdleMode::IdleMode(EntityService& entityService, ModeController& modeController)
    : BasicMode(entityService, modeController)
{}

void IdleMode::Enter(std::shared_ptr<BasicEvent> event)
{
    shape_->SetAnimation(GetAnimation());
    shape_->SetImage(GetImage());
}

void IdleMode::Register()
{
    shape_ = Service().GetShape();
}

void IdleMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);
    BasicUpdate();
}

}  // namespace Entity

}  // namespace FA
