/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/PropertyData.h"
#include "Resource/Animation.h"

namespace FA {

namespace Entity {

TileEntity::TileEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                       EntityManager& entityManager, MessageBus& messageBus)
    : BasicEntity(id, cameraManager, sheetManager, entityManager, messageBus)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterModes(ModeController& modeController)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);
}

void TileEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Undefined);
}

void TileEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const PropertyData& data)
{
    auto idleMode = modeController.GetMode(ModeType::Idle);
    auto& mUndef = idleMode->AddDirection(FaceDirection::Undefined);
    float t = constant::Entity::stdSwitchTime;
    mUndef.animation_ = Animation(data.frames_, 0, t);
}

}  // namespace Entity

}  // namespace FA
