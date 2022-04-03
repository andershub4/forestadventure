/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackWeaponMode.h"

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
    auto dir = Service().GetProperty<FaceDirection>("FaceDirection");
    shape_->SetAnimation(GetAnimation(dir));
    shape_->SetImage(GetImage(dir));
    offset_ = m->offset_.at(dir);
    rotation_ = m->rotation_.at(dir);
    entityType_ = m->entityType_;
}

void AttackWeaponMode::Exit()
{
    auto dir = Service().GetProperty<FaceDirection>("FaceDirection");
    auto position = Service().GetProperty<sf::Vector2f>("Position") + offset_;
    Service().SpawnEntity(entityType_, dir, position, rotation_);
}

void AttackWeaponMode::Register()
{
    shape_ = Service().GetShape();
}

void AttackWeaponMode::Update(float deltaTime)
{
    shape_->Update(deltaTime);
    BasicUpdate();
}

}  // namespace Entity

}  // namespace FA
