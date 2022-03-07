/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

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

namespace {

std::unordered_map<std::string, AnimationData> animationDatas = {
    {"Move_Left", {SheetId::MoleWalkSide, {{0, 0}, 4, 0}, true}},
    {"Move_Right", {SheetId::MoleWalkSide, {{0, 0}, 4, 0}, false}},
    {"Move_Down", {SheetId::MoleWalkFront, {{0, 0}, 4, 0}, false}},
    {"Move_Up", {SheetId::MoleWalkBack, {{0, 0}, 4, 0}, false}},
    {"Idle_Left", {SheetId::MoleIdleSide, {{0, 0}, 1, 0}, true}},
    {"Idle_Right", {SheetId::MoleIdleSide, {{0, 0}, 1, 0}, false}},
    {"Idle_Down", {SheetId::MoleIdleFront, {{0, 0}, 1, 0}, false}},
    {"Idle_Up", {SheetId::MoleIdleBack, {{0, 0}, 1, 0}, false}}};
}

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
    entityService.AddAttribute<FaceDirectionAttribute>();
    entityService.AddAttribute<VelocityAttribute>();
}

void MoleEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const AttributeData& data)
{
    auto idleMode = modeController.GetMode(ModeType::Idle);

    auto& ileft = idleMode->AddDirection(FaceDirection::Left);
    auto& iright = idleMode->AddDirection(FaceDirection::Right);
    auto& iup = idleMode->AddDirection(FaceDirection::Up);
    auto& idown = idleMode->AddDirection(FaceDirection::Down);
    ileft.animation_ = entityService.MakeAnimation(animationDatas.at("Idle_Left"));
    iright.animation_ = entityService.MakeAnimation(animationDatas.at("Idle_Right"));
    iup.animation_ = entityService.MakeAnimation(animationDatas.at("Idle_Up"));
    idown.animation_ = entityService.MakeAnimation(animationDatas.at("Idle_Down"));

    auto moveMode = modeController.GetMode(ModeType::Move);

    auto& mleft = moveMode->AddDirection(FaceDirection::Left);
    auto& mright = moveMode->AddDirection(FaceDirection::Right);
    auto& mup = moveMode->AddDirection(FaceDirection::Up);
    auto& mdown = moveMode->AddDirection(FaceDirection::Down);
    mleft.animation_ = entityService.MakeAnimation(animationDatas.at("Move_Left"));
    mright.animation_ = entityService.MakeAnimation(animationDatas.at("Move_Right"));
    mup.animation_ = entityService.MakeAnimation(animationDatas.at("Move_Up"));
    mdown.animation_ = entityService.MakeAnimation(animationDatas.at("Move_Down"));
}

void MoleEntity::InitAttributes(const EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.GetAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    auto f = entityService.GetAttribute<FaceDirectionAttribute>();
    f->SetDirection(data.faceDir_);
    auto v = entityService.GetAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
}

}  // namespace Entity

}  // namespace FA
