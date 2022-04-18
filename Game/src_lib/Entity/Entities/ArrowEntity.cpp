/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/PropertyData.h"
#include "Entity/States/IdleState.h"
#include "Entity/States/MoveState.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

ArrowEntity::ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::RegisterStates(StateMachine& stateMachine)
{
    auto idleState = stateMachine.RegisterState<IdleState>(true);
    idleState->BindAction(Action::ChangeTo(StateType::Move), EventType::StartMove);
    idleState->BindAction(Action::Ignore(), EventType::Collision);

    auto moveState = stateMachine.RegisterState<MoveState>();
    moveState->BindAction(Action::ChangeTo(StateType::Idle), EventType::StopMove);
}

void ArrowEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity * 8.0f);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void ArrowEntity::BuildImages(const EntityService& entityService, StateType stateType)
{
    image_ = entityService.MakeImage({SheetId::Arrow, {0, 0}});
}

Image ArrowEntity::GetImage(const EntityService& entityService, StateType stateType) const
{
    return image_;
}

void ArrowEntity::InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                             const PropertyData& data)
{
    auto moveState = stateMachine.GetState(StateType::Move);
    auto stateType = moveState->GetStateType();

    BuildImages(entityService, StateType::Idle);
    moveState->SetImageFn(
        [this, stateType](const EntityService& entityService) { return GetImage(entityService, stateType); });
}

void ArrowEntity::PostUpdate(EntityService& entityService)
{
    auto position = entityService.GetProperty<sf::Vector2f>("Position");
    auto mapW = static_cast<float>(entityService.GetMapSize().x);
    auto mapH = static_cast<float>(entityService.GetMapSize().y);
    auto mapRect = sf::FloatRect(0, 0, mapW, mapH);
    bool outsideMap = !mapRect.contains(position);

    if (outsideMap) {
        entityService.DeleteEntity(GetId());
    }
}

}  // namespace Entity

}  // namespace FA
