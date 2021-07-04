/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/Sprite.h"
#include "Entity/Configuration.h"
#include "Message/MessageBus.h"
#include "Resource/AnimationManager.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, MessageBus& messageBus)
    : BasicEntity(id, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(AnimationManager& animationManager, Camera& camera, const Configuration& configuration)
{
    auto db = animationManager.GetDB(AnimationType::Mole);

    InitStateData(configuration.faceDir_, configuration.velocity_, configuration.position_, configuration.scale_, db);
}

void MoleEntity::OnDestroy()
{}

}  // namespace Entity

}  // namespace FA
