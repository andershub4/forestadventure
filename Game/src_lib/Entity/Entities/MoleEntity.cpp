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
#include "Entity/PropertyData.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, CameraManager& cameraManager, MessageBus& messageBus)
    : BasicEntity(id, EntityType::Mole, cameraManager, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(EntityService& handler, const PropertyData& data)
{
    auto t = handler.AddAttribute<TransformAttribute>();
    t->SetPosition(data.position_);
    t->SetScale(data.scale_);
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    auto f = handler.AddAttribute<FaceDirectionAttribute>();
    f->SetAvailableDirections(dirs);
    auto v = handler.AddAttribute<VelocityAttribute>();
    v->SetVelocity(data.velocity_);
    handler.AddBehavior<MovementBehavior>();
    auto a = handler.AddAttribute<AnimationAttribute>();
    auto s = handler.AddAttribute<ShapeAttribute>();
    s->AddAnimation(a);
}

void MoleEntity::OnInit(const AnimationDb& animationDb)
{
    InitStateData(animationDb);
}

}  // namespace Entity

}  // namespace FA
