/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/PropertyData.h"
#include "Entity/States/IdleState.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

CoinEntity::CoinEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterStates(StateMachine& stateMachine)
{
    auto idleState = stateMachine.RegisterState<IdleState>(true);
    idleState->BindAction(Action::Ignore(), EventType::Collision);
}

void CoinEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Undefined);
}

void CoinEntity::BuildAnimations(const EntityService& entityService, StateType stateType)
{
    animation_ = entityService.MakeAnimation({SheetId::Coin, {{0, 0}, 4, 0}, false});
}

Animation CoinEntity::GetAnimation(const EntityService& entityService, StateType stateType) const
{
    return animation_;
}

void CoinEntity::InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                            const PropertyData& data)
{
    auto idleState = stateMachine.GetState(StateType::Idle);
    auto stateType = idleState->GetStateType();

    BuildAnimations(entityService, StateType::Idle);
    idleState->SetAnimationFn(
        [this, stateType](const EntityService& entityService) { return GetAnimation(entityService, stateType); });
}

}  // namespace Entity

}  // namespace FA
