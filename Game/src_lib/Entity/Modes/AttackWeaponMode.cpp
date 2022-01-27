/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponMode.h"

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/EntityService.h"
#include "Entity/Events/AttackWeapon.h"
#include "Entity/Shape.h"

namespace FA {

namespace Entity {

AttackWeaponMode::AttackWeaponMode(EntityService& entityService, ModeController& modeController)
    : BasicMode(entityService, modeController)
{}

void AttackWeaponMode::Enter(std::shared_ptr<BasicEvent> event)
{
    auto m = std::dynamic_pointer_cast<AttackWeaponEvent>(event);
    auto dir = faceDirection_->GetDirection();
    shape_->SetAnimation(GetAnimation(dir));
    shape_->SetImage(GetImage(dir));
    offset_ = m->offset_.at(dir);
    entityType_ = m->entityType_;
    velocity_ = m->velocity_;
}

void AttackWeaponMode::Exit()
{
    auto dir = faceDirection_->GetDirection();
    auto position = transform_->GetPosition() + offset_;
    auto scale = transform_->GetScale();
    Service().SpawnEntity(entityType_, dir, position, scale, velocity_);
}

void AttackWeaponMode::Register()
{
    transform_ = Service().GetAttribute<TransformAttribute>();
    faceDirection_ = Service().GetAttribute<FaceDirectionAttribute>();
    shape_ = Service().GetShape();
}

void AttackWeaponMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);
    BasicUpdate();
}

}  // namespace Entity

}  // namespace FA
