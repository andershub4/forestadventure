/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackMode.h"

#include "Entity/EntityService.h"
#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

AttackMode::AttackMode(EntityService &entityService)
    : BasicMode(entityService)
{}

void AttackMode::Enter(std::shared_ptr<BasicEvent> event)
{
    shape_->Set(FrameType::Attack);
}

void AttackMode::Awake()
{
    shape_ = Service().GetShape();
}

void AttackMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);
}

}  // namespace Entity

}  // namespace FA
