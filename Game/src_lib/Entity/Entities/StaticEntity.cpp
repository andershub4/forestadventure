/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "StaticEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/SpriteComponent.h"
#include "Message/MessageBus.h"
#include "Resource/TextureManager.h"

namespace FA {

namespace Entity {

StaticEntity::StaticEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : BasicEntity(id, messageBus, textureManager)
{}

StaticEntity::~StaticEntity() = default;

}  // namespace Entity

}  // namespace FA
