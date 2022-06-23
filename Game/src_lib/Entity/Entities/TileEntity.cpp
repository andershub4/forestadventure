/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Abilities/AnimationAbility.h"
#include "Entity/PropertyData.h"
#include "Entity/States/State.h"

namespace FA {

namespace Entity {

TileEntity::TileEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

TileEntity::~TileEntity() = default;

void TileEntity::OnUpdateAnimation(const Animation& animation)
{
    auto& sprite = shape_.GetSprite("Main");
    animation.ApplyTo(sprite);
}

void TileEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
    propertyManager_.Register<float>("Rotation", 0.0);
}

void TileEntity::RegisterShape()
{
    shape_ = CreateShape();
    shape_.AddSprite("Main");
}

void TileEntity::RegisterStates(const PropertyData& data)
{
    auto getKey = [this]() { return "Idle"; };
    auto updateAnimation = [this](const Animation& animation) { OnUpdateAnimation(animation); };

    auto idleState = RegisterState(StateType::Idle, true);
    auto idleAnimation = std::make_shared<AnimationAbility>(getKey, updateAnimation);
    float t = constant::Entity::stdSwitchTime;
    auto a = Animation(data.frames_, 0, t);
    idleAnimation->RegisterAnimation("Idle", a);
    idleState->RegisterAbility(idleAnimation);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

}  // namespace Entity

}  // namespace FA
