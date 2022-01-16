/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Entity/PropertyData.h"
#include "Entity/Shapes/AnimationShape.h"
#include "Entity/Shapes/ImageShape.h"
#include "Entity/Shapes/Shape.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

FrameType ModeTypeToFrameType(ModeType modeType)
{
    switch (modeType) {
        case ModeType::Idle:
            return FrameType::Idle;
        case ModeType::Move:
            return FrameType::Move;
        default:
            return FrameType::Undefined;
    }
}

}  // namespace

ArrowEntity::ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

ArrowEntity::~ArrowEntity() = default;

std::vector<ImageData> ArrowEntity::Images() const
{
    std::vector<ImageData> data = {{SheetId::Arrow, {0, 0}, 270.0f, FrameType::Idle, FaceDirection::Left},
                                   {SheetId::Arrow, {0, 0}, 90.0f, FrameType::Idle, FaceDirection::Right},
                                   {SheetId::Arrow, {0, 0}, 180.0f, FrameType::Idle, FaceDirection::Down},
                                   {SheetId::Arrow, {0, 0}, 0.0f, FrameType::Idle, FaceDirection::Up},
                                   {SheetId::Arrow, {0, 0}, 270.0f, FrameType::Move, FaceDirection::Left},
                                   {SheetId::Arrow, {0, 0}, 90.0f, FrameType::Move, FaceDirection::Right},
                                   {SheetId::Arrow, {0, 0}, 180.0f, FrameType::Move, FaceDirection::Down},
                                   {SheetId::Arrow, {0, 0}, 0.0f, FrameType::Move, FaceDirection::Up}};

    return data;
}

void ArrowEntity::DefineProperties(EntityService& entityService, const PropertyData& data)
{
    auto t = entityService.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    auto f = entityService.AddAttribute<FaceDirectionAttribute>();
    f->SetAvailableDirections(dirs);
    auto v = entityService.AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
}

void ArrowEntity::DefineModes(ModeController& modeController)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.RegisterMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
}

void ArrowEntity::DefineShape(EntityService& entityService, Shape& shape)
{
    auto lookupKeyFunc = [](FrameType frameType, FaceDirection faceDir) {
        std::stringstream ss;
        ss << frameType << "_" << faceDir;
        return ss.str();
    };

    auto i = std::make_shared<ImageShape>(lookupKeyFunc);
    auto dirs = entityService.GetAttribute<FaceDirectionAttribute>()->GetAvailableDirections();

    for (auto modeType : entityService.GetModeTypes()) {
        auto frameType = ModeTypeToFrameType(modeType);
        if (frameType == FrameType::Undefined) continue;
        for (auto faceDir : dirs) {
            auto image = entityService.GetImage(Type(), frameType, faceDir);
            i->AddImage(frameType, faceDir, image);
        }
    }

    shape.AddImageShape(i);
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
