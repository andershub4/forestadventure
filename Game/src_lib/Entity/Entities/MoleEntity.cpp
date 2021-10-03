/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/AnimationAttribute.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/SpriteAttribute.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, const PropertyHandler& propertyHandler, MessageBus& messageBus)
    : BasicEntity(id, propertyHandler, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate()
{
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    auto f = AddAttribute<FaceDirectionAttribute>();
    f->SetAvailableDirections(dirs);
    AddBehavior<MovementBehavior>();
    auto a = AddAttribute<AnimationAttribute>();
    auto s = AddAttribute<SpriteAttribute>();
    s->AddAnimation(a);
}

void MoleEntity::OnInit(const AnimationDb& animationDb)
{
    InitStateData(animationDb);
}

}  // namespace Entity

}  // namespace FA
