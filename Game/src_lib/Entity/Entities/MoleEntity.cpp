/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Entity/PropertyData.h"
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

void MoleEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
    entityService.RegisterProperty<std::vector<FaceDirection>>(
        "FaceDirections", {FaceDirection::Down, FaceDirection::Up, FaceDirection::Left, FaceDirection::Right});
}

void MoleEntity::BuildAnimations(const EntityService& entityService, ModeType modeType)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");
    auto modeData = animationDatas.at(modeType);
    auto& m = animations_[modeType];

    for (auto direction : directions) {
        m[direction] = entityService.MakeAnimation(modeData.at(direction));
    }
}

Animation MoleEntity::GetAnimation(const EntityService& entityService, ModeType modeType) const
{
    auto dir = entityService.GetProperty<FaceDirection>("FaceDirection");

    return animations_.at(modeType).at(dir);
}

void MoleEntity::InitMode(std::shared_ptr<BasicMode> mode, const std::vector<FaceDirection>& directions,
                          const EntityService& entityService)
{
    auto modeType = mode->GetModeType();
    auto modeData = animationDatas.at(modeType);

    BuildAnimations(entityService, modeType);
    mode->SetAnimationFn(
        [this, modeType](const EntityService& entityService) { return GetAnimation(entityService, modeType); });
}

void MoleEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const PropertyData& data)
{
    auto directions = entityService.GetProperty<std::vector<FaceDirection>>("FaceDirections");

    InitMode(modeController.GetMode(ModeType::Idle), directions, entityService);
    InitMode(modeController.GetMode(ModeType::Move), directions, entityService);
}

}  // namespace Entity

}  // namespace FA
