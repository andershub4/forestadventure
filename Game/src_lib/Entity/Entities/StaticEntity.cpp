/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StaticEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/StaticSprite.h"
#include "Entity/Configuration.h"
#include "Message/MessageBus.h"
#include "Resource/TileSet.h"

namespace FA {

namespace Entity {

StaticEntity::StaticEntity(EntityId id, MessageBus& messageBus)
    : BasicEntity(id, messageBus)
{}

StaticEntity::~StaticEntity() = default;

void StaticEntity::OnCreate(AnimationManager& animationManager, TileSet& tileSet, Camera& camera,
                            const Configuration& configuration)
{
    auto stoneTile = tileSet.GetTile(configuration.tileType_);
    auto sprite = std::make_unique<Entity::StaticSprite>(configuration.position_, stoneTile.texture_, stoneTile.rect_);

    InitStateData(configuration.faceDir_, configuration.velocity_, std::move(sprite));
}

void StaticEntity::OnDestroy()
{}

}  // namespace Entity

}  // namespace FA
