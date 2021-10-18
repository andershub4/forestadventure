/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/AnimationAttribute.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/ShapeAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/Attributes/VelocityAttribute.h"
#include "Entity/Behaviors/MovementBehavior.h"
#include "Entity/PropertyData.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, CameraManager& cameraManager, const AnimationDb& animationDb,
                       MessageBus& messageBus)
    : BasicEntity(id, EntityType::Mole, cameraManager, animationDb, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnAddProperties(EntityService& entityService, const PropertyData& data)
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
    entityService.AddBehavior<MovementBehavior>();
    auto a = entityService.AddAttribute<AnimationAttribute>();
    auto s = entityService.AddAttribute<ShapeAttribute>();
    s->AddAnimation(a);
}

void MoleEntity::OnInit()
{
    InitStateData();
}

}  // namespace Entity

}  // namespace FA
