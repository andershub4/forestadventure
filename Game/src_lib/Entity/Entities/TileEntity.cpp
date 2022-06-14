/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AnimationSprite.h"
#include "Entity/PropertyData.h"
#include "Entity/States/BasicState.h"

namespace FA {

namespace Entity {

TileEntity::TileEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterProperties()
{
    propertyManager_.Register<sf::Vector2f>("Position", {0.0, 0.0});
}

void TileEntity::OnUpdateShape(Shape& shape)
{
    shape.SetPosition(propertyManager_.Get<sf::Vector2f>("Position"));
}

void TileEntity::RegisterShapes(const PropertyData& data)
{
    auto shape = std::make_shared<Shape>([this](Shape& shape) { OnUpdateShape(shape); });

    auto getKey = [this](StateType stateType) {
        std::stringstream ss;
        ss << stateType;
        return ss.str();
    };

    auto sprite = std::make_shared<AnimationSprite>(getKey);

    float t = constant::Entity::stdSwitchTime;
    auto a = Animation(data.frames_, 0, t);
    sprite->RegisterAnimation("Idle", a);

    shape->RegisterAnimationSprite("Main", sprite);

    RegisterShape("Main", shape);
}

void TileEntity::RegisterStates()
{
    auto idleState = RegisterState(StateType::Idle, true);
    idleState->AddShape("Main", nullptr);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

}  // namespace Entity

}  // namespace FA
