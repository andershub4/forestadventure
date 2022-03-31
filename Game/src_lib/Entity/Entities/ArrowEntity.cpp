/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AttributeData.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

std::unordered_map<std::string, ImageData> imageDatas = {{"Left", {SheetId::Arrow, {0, 0}, 270.0f}},
                                                         {"Right", {SheetId::Arrow, {0, 0}, 90.0f}},
                                                         {"Down", {SheetId::Arrow, {0, 0}, 180.0f}},
                                                         {"Up", {SheetId::Arrow, {0, 0}, 0.0f}}};

}

ArrowEntity::ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

ArrowEntity::~ArrowEntity() = default;

void ArrowEntity::RegisterModes(ModeController& modeController)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.RegisterMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
}

void ArrowEntity::RegisterAttributes(EntityService& entityService)
{
    entityService.AddAttribute<TransformAttribute>();
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity * 8.0f);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void ArrowEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                            const AttributeData& data)
{
    auto moveMode = modeController.GetMode(ModeType::Move);

    auto& mleft = moveMode->AddDirection(FaceDirection::Left);
    auto& mright = moveMode->AddDirection(FaceDirection::Right);
    auto& mup = moveMode->AddDirection(FaceDirection::Up);
    auto& mdown = moveMode->AddDirection(FaceDirection::Down);
    mleft.image_ = entityService.MakeImage(imageDatas.at("Left"));
    mright.image_ = entityService.MakeImage(imageDatas.at("Right"));
    mup.image_ = entityService.MakeImage(imageDatas.at("Up"));
    mdown.image_ = entityService.MakeImage(imageDatas.at("Down"));
}

void ArrowEntity::InitAttributes(const EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.GetAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
}

void ArrowEntity::PostUpdate(EntityService& entityService)
{
    auto position = entityService.GetAttribute<TransformAttribute>()->GetPosition();
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
