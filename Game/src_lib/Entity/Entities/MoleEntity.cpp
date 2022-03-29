/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/AttributeData.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

namespace {

const std::unordered_map<ModeType, std::unordered_map<FaceDirection, AnimationData>> animationDatas = {
    {ModeType::Move,
     {{FaceDirection::Left, {SheetId::MoleWalkSide, {{0, 0}, 4, 0}, true}},
      {FaceDirection::Right, {SheetId::MoleWalkSide, {{0, 0}, 4, 0}, false}},
      {FaceDirection::Down, {SheetId::MoleWalkFront, {{0, 0}, 4, 0}, false}},
      {FaceDirection::Up, {SheetId::MoleWalkBack, {{0, 0}, 4, 0}, false}}}},
    {ModeType::Idle,
     {{FaceDirection::Left, {SheetId::MoleIdleSide, {{0, 0}, 1, 0}, true}},
      {FaceDirection::Right, {SheetId::MoleIdleSide, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Down, {SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}},
      {FaceDirection::Up, {SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}}}}};

}  // namespace

MoleEntity::MoleEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::RegisterModes(ModeController& modeController)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::ChangeTo(ModeType::Move), EventType::StartMove);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);

    auto moveMode = modeController.RegisterMode<MoveMode>();
    moveMode->BindAction(Action::ChangeTo(ModeType::Idle), EventType::StopMove);
}

void MoleEntity::RegisterAttributes(EntityService& entityService)
{
    entityService.AddAttribute<TransformAttribute>();
    entityService.AddAttribute<VelocityAttribute>();
    entityService.Register<FaceDirection>("FaceDirection", FaceDirection::Down);
    entityService.Register<std::vector<FaceDirection>>(
        "FaceDirections", {FaceDirection::Down, FaceDirection::Up, FaceDirection::Left, FaceDirection::Right});
}

void MoleEntity::InitMode(std::shared_ptr<BasicMode> mode, const std::vector<FaceDirection>& directions,
                          const EntityService& entityService)
{
    auto modeType = mode->GetModeType();
    auto modeData = animationDatas.at(modeType);

    for (auto direction : directions) {
        auto& d = mode->AddDirection(direction);
        d.animation_ = entityService.MakeAnimation(modeData.at(direction));
    }
}

void MoleEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const AttributeData& data)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");

    InitMode(modeController.GetMode(ModeType::Idle), directions, entityService);
    InitMode(modeController.GetMode(ModeType::Move), directions, entityService);
}

void MoleEntity::InitAttributes(const EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.GetAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    auto v = entityService.GetAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
}

}  // namespace Entity

}  // namespace FA
