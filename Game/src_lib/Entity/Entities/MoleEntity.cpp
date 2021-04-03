/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/AnimatedSprite.h"
#include "Entity/Components/Sprite/BasicSprite.h"
#include "Entity/Configuration.h"
#include "Message/MessageBus.h"
#include "Resource/AnimationManager.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, MessageBus& messageBus)
    : BasicEntity(id, messageBus)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(AnimationManager& animationManager, TileSet& tileSet, Camera& camera,
                          const Configuration& configuration)
{
    auto animationFactory = animationManager.GetFactory(AnimationType::Mole);
    auto sprite = std::make_unique<Entity::AnimatedSprite>(configuration.position_, animationFactory);

    InitStateData(configuration.faceDir_, configuration.velocity_, std::move(sprite));
}

void MoleEntity::OnDestroy()
{}

}  // namespace Entity

}  // namespace FA
