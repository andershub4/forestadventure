/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/AnimationManager.h"
#include "Entity/Components/Sprite/Sprite.h"
#include "Entity/Configuration.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, MessageBus& messageBus)
    : BasicEntity(id, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(AnimationManager& animationManager, const Configuration& configuration)
{
    auto db = animationManager.GetDB(AnimationType::Mole);

    InitStateData(configuration, db);
}

}  // namespace Entity

}  // namespace FA
