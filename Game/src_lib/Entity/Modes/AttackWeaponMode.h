/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "BasicMode.h"

#include "Enum/EntityType.h"

namespace FA {

namespace Entity {

class TransformAttribute;

class AttackWeaponMode : public BasicMode
{
public:
    AttackWeaponMode(EntityService& entityService, ModeController& modeController);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;
    virtual void Exit() override;

    virtual void Register() override;
    virtual void Update(float deltaTime) override;
    virtual ModeType GetModeType() const override { return ModeType::AttackWeapon; }

private:
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<Shape> shape_ = nullptr;
    EntityType entityType_ = EntityType::Unknown;
    sf::Vector2f offset_;
    float velocity_ = 0.0f;
};

}  // namespace Entity

}  // namespace FA
