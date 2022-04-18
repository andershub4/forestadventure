/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/PropertyData.h"
#include "Entity/States/IdleState.h"

namespace FA {

namespace Entity {

TileEntity::TileEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterStates(StateMachine& stateMachine)
{
    auto idleState = stateMachine.RegisterState<IdleState>(true);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

void TileEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Undefined);
}

void TileEntity::InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                            const PropertyData& data)
{
    auto idleState = stateMachine.GetState(StateType::Idle);

    float t = constant::Entity::stdSwitchTime;
    animation_ = Animation(data.frames_, 0, t);
    idleState->SetAnimationFn([this](const EntityService& entityService) { return animation_; });
}

}  // namespace Entity

}  // namespace FA
