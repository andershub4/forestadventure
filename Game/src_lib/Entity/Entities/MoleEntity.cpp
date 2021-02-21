/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/BasicSprite.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(MessageBus& messageBus, std::unique_ptr<BasicSprite> sprite, FaceDirection faceDir, float speed)
    : BasicEntity(messageBus, std::move(sprite), faceDir, speed)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate()
{}

void MoleEntity::OnDestroy()
{}

}  // namespace Entity

}  // namespace FA
