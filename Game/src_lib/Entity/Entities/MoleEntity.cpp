/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/AnimationComponent.h"
#include "Entity/Components/FaceDirectionComponent.h"
#include "Entity/Components/SpriteComponent.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, const ComponentHandler& componentHandler, MessageBus& messageBus)
    : BasicEntity(id, componentHandler, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate()
{
    std::vector<FaceDirection> dirs = {FaceDirection::Down, FaceDirection::Left, FaceDirection::Right,
                                       FaceDirection::Up};
    AddComponent<FaceDirectionComponent>(dirs);
    AddComponent<MovementComponent>();
    auto a = AddComponent<AnimationComponent>();
    auto s = AddComponent<SpriteComponent>();
    s->AddAnimation(a);
}

void MoleEntity::OnInit(const AnimationDb& animationDb)
{
    InitStateData(animationDb);
}

}  // namespace Entity

}  // namespace FA
