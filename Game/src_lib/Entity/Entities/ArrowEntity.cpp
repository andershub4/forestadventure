/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/AttributeData.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

ArrowEntity::ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

ArrowEntity::~ArrowEntity() = default;

std::vector<ImageData> ArrowEntity::ImageDataStore() const
{
    std::vector<ImageData> data = {{SheetId::Arrow, {0, 0}, 270.0f, FrameType::Move, FaceDirection::Left},
                                   {SheetId::Arrow, {0, 0}, 90.0f, FrameType::Move, FaceDirection::Right},
                                   {SheetId::Arrow, {0, 0}, 180.0f, FrameType::Move, FaceDirection::Down},
                                   {SheetId::Arrow, {0, 0}, 0.0f, FrameType::Move, FaceDirection::Up}};

    return data;
}

void ArrowEntity::AddAttributes(EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    auto f = entityService.AddAttribute<FaceDirectionAttribute>();
    f->SetDirection(data.faceDir_);
    auto v = entityService.AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
}

void ArrowEntity::RegisterModes(ModeController& modeController, const EntityService& entityService)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.RegisterMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);

    auto& mleft = moveMode->AddDirection(FaceDirection::Left);
    auto& mright = moveMode->AddDirection(FaceDirection::Right);
    auto& mup = moveMode->AddDirection(FaceDirection::Up);
    auto& mdown = moveMode->AddDirection(FaceDirection::Down);
    mleft.image_ = entityService.GetImage(Type(), FrameType::Move, FaceDirection::Left);
    mright.image_ = entityService.GetImage(Type(), FrameType::Move, FaceDirection::Right);
    mup.image_ = entityService.GetImage(Type(), FrameType::Move, FaceDirection::Up);
    mdown.image_ = entityService.GetImage(Type(), FrameType::Move, FaceDirection::Down);
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
