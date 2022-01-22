/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponMode.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/EntityService.h"
#include "Entity/Shape.h"

namespace FA {

namespace Entity {

AttackWeaponMode::AttackWeaponMode(EntityService &entityService)
    : BasicMode(entityService)
{}

void AttackWeaponMode::Enter(std::shared_ptr<BasicEvent> event)
{
    auto dir = faceDirection_->GetDirection();
    shape_->SetAnimation(GetAnimation(dir));
    shape_->SetImage(GetImage(dir));

    Service().SpawnEntity();
}

void AttackWeaponMode::Register()
{
    faceDirection_ = Service().GetAttribute<FaceDirectionAttribute>();
    shape_ = Service().GetShape();
}

void AttackWeaponMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);
}

}  // namespace Entity

}  // namespace FA
