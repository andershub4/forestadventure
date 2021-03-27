/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Fwd/SfmlFwd.h"
#include "Entity/Id.h"
#include "Resource/AnimationManager.h"
#include "Resource/TileSet.h"
#include "Tile/TileMap.h"

namespace FA {

namespace Entity {
class BasicEntity;
}

class TextureManager;
class MessageBus;
class Camera;

class Level
{
public:
    Level(TextureManager& textureManager);
    ~Level();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);

    void Create(MessageBus &messageBus, Camera &camera);
    void EnableInput(bool enable);
    sf::Vector2u GetSize() const;

private:
    AnimationManager animationManager_;
    TileSet tileSet_;
    std::unique_ptr<Entity::BasicEntity> entity_;
    std::unique_ptr<Entity::BasicEntity> moleEntity_;
    std::unique_ptr<Entity::BasicEntity> stoneEntity_;
    Tile::TileMap tileMap_;
    Entity::EntityId entityId_ = 0;

private:
    Entity::EntityId GenerateEntityId();
};

}  // namespace FA
