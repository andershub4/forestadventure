/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ArrowEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "Entity/Modes/IdleMode.h"
#include "Entity/Modes/MoveMode.h"
#include "Entity/PropertyData.h"
#include "Resource/SheetId.h"

namespace FA {

namespace Entity {

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

void ArrowEntity::RegisterProperties(EntityService& entityService)
{
    entityService.RegisterProperty<float>("Rotation", 0.0);
    entityService.RegisterProperty<float>("Scale", 1.0);
    entityService.RegisterProperty<sf::Vector2f>("Position", {0.0, 0.0});
    entityService.RegisterProperty<float>("Velocity", constant::Entity::stdVelocity * 8.0f);
    entityService.RegisterProperty<FaceDirection>("FaceDirection", FaceDirection::Down);
}

void ArrowEntity::BuildImages(const EntityService& entityService, ModeType modeType)
{
    image_ = entityService.MakeImage({SheetId::Arrow, {0, 0}});
}

Image ArrowEntity::GetImage(const EntityService& entityService, ModeType modeType) const
{
    return image_;
}

void ArrowEntity::InitModes(const ModeController& modeController, const EntityService& entityService,
                            const PropertyData& data)
{
    auto moveMode = modeController.GetMode(ModeType::Move);
    auto modeType = moveMode->GetModeType();

    BuildImages(entityService, ModeType::Idle);
    moveMode->SetImageFn(
        [this, modeType](const EntityService& entityService) { return GetImage(entityService, modeType); });
}

void ArrowEntity::PostUpdate(EntityService& entityService)
{
    auto position = entityService.GetProperty<sf::Vector2f>("Position");
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
