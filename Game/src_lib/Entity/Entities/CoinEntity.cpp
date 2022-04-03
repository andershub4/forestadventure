/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/PropertyData.h"
#include "Resource/Animation.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

std::unordered_map<std::string, AnimationData> animationDatas = {{"Undefined", {SheetId::Coin, {{0, 0}, 4, 0}, false}}};

}

CoinEntity::CoinEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

CoinEntity::~CoinEntity() = default;

void CoinEntity::RegisterModes(ModeController& modeController)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);
}

void CoinEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Undefined);
}

void CoinEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const PropertyData& data)
{
    auto idleMode = modeController.GetMode(ModeType::Idle);
    auto& mUndef = idleMode->AddDirection(FaceDirection::Undefined);
    mUndef.animation_ = entityService.MakeAnimation(animationDatas.at("Undefined"));
}

}  // namespace Entity

}  // namespace FA
