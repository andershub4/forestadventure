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

namespace FA {

namespace Entity {

StaticEntity::StaticEntity(EntityId id, MessageBus& messageBus)
    : BasicEntity(id, messageBus)
{}

StaticEntity::~StaticEntity() = default;

}  // namespace Entity

}  // namespace FA
