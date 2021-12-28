/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Entity/PropertyData.h"
#include "Entity/Shapes/AnimationShape.h"
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

MoleEntity::MoleEntity(EntityId id, CameraManager& cameraManager, TextureManager& textureManager,
                       MessageBus& messageBus)
    : BasicEntity(id, cameraManager, textureManager, messageBus)
{}

MoleEntity::~MoleEntity() = default;

std::vector<AnimationData> MoleEntity::Animations() const
{
    std::vector<AnimationData> data = {
        {SheetId::MoleWalkSide, {{0, 0}, 6, 0, true}, FrameType::Move, FaceDirection::Left},
        {SheetId::MoleWalkSide, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Right},
        {SheetId::MoleWalkFront, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Down},
        {SheetId::MoleWalkBack, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Up},
        {SheetId::MoleIdleSide, {{0, 0}, 1, 0, true}, FrameType::Idle, FaceDirection::Left},
        {SheetId::MoleIdleSide, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Right},
        {SheetId::MoleIdleFront, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Down},
        {SheetId::MoleIdleBack, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Up}};

    return data;
}

void MoleEntity::DefineProperties(EntityService& entityService, const PropertyData& data)
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

void MoleEntity::DefineModes(ModeController& modeController)
{
    auto idleMode = modeController.AddMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.AddMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
}

void MoleEntity::DefineShape(EntityService& entityService, Shape& shape)
{
    auto lookupKeyFunc = [](FrameType frameType, FaceDirection faceDir) {
        std::stringstream ss;
        ss << frameType << "_" << faceDir;
        return ss.str();
    };

    auto a = std::make_shared<AnimationShape>(lookupKeyFunc);
    auto dirs = entityService.GetAttribute<FaceDirectionAttribute>()->GetAvailableDirections();

    for (auto modeType : entityService.GetModeTypes()) {
        auto frameType = ModeTypeToFrameType(modeType);
        if (frameType == FrameType::Undefined) continue;
        for (auto faceDir : dirs) {
            auto animation = entityService.GetAnimation(Type(), frameType, faceDir);
            a->AddAnimation(frameType, faceDir, animation);
        }
    }

    shape.AddAnimationShape(a);
}

}  // namespace Entity

}  // namespace FA
