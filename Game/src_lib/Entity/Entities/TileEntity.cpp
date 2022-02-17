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

void TileEntity::AddAttributes(EntityService& entityService, const AttributeData& data)
{
    auto t = entityService.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    auto f = entityService.AddAttribute<FaceDirectionAttribute>();
    f->SetDirection(data.faceDir_);
    frames_ = data.frames_;
}

void TileEntity::RegisterModes(ModeController& modeController, const EntityService& entityService)
{
    auto idleMode = modeController.RegisterMode<IdleMode>(true);
    auto& mUndef = idleMode->AddDirection(FaceDirection::Undefined);
    idleMode->BindAction(Action::Ignore(), EventType::Collision);
    float t = constant::Entity::stdSwitchTime;
    mUndef.animation_ = Animation(frames_, 0, t);
}

}  // namespace Entity

}  // namespace FA
