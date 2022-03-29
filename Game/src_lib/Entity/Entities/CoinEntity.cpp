/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "CoinEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AttributeData.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Modes/IdleMode.h"
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

void CoinEntity::RegisterAttributes(EntityService& entityService)
{
    entityService.AddAttribute<TransformAttribute>();
    entityService.AddAttribute<FaceDirectionAttribute>();
    entityService.Register<FaceDirection>("FaceDirection", FaceDirection::Undefined);
}

void CoinEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const AttributeData& data)
{
    auto idleMode = modeController.GetMode(ModeType::Idle);
    auto& mUndef = idleMode->AddDirection(FaceDirection::Undefined);
    mUndef.animation_ = entityService.MakeAnimation(animationDatas.at("Undefined"));
}

void CoinEntity::InitAttributes(const EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.GetAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
}

}  // namespace Entity

}  // namespace FA
