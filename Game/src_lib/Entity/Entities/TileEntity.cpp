/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/AttributeData.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Modes/IdleMode.h"
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

void TileEntity::RegisterAttributes(EntityService& entityService)
{
    entityService.AddAttribute<TransformAttribute>();
    entityService.AddAttribute<FaceDirectionAttribute>();
}

void TileEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                           const AttributeData& data)
{
    auto idleMode = modeController.GetMode(ModeType::Idle);
    auto& mUndef = idleMode->AddDirection(FaceDirection::Undefined);
    float t = constant::Entity::stdSwitchTime;
    mUndef.animation_ = Animation(data.frames_, 0, t);
}

void TileEntity::InitAttributes(EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.GetAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    auto f = entityService.GetAttribute<FaceDirectionAttribute>();
    f->SetDirection(data.faceDir_);
}

}  // namespace Entity

}  // namespace FA
