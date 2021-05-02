/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Fwd/SfmlFwd.h"
#include "Resource/AnimationManager.h"
#include "System/EntitySystem.h"
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
    Level(MessageBus& messageBus, const Tile::TileMapData& tileMapData, TextureManager& textureManager);
    ~Level();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);

    void Create(Camera& camera);
    void EnableInput(bool enable);
    sf::Vector2u GetSize() const;

private:
    AnimationManager animationManager_;
    EntitySystem entitySystem_;
    Tile::TileMap tileMap_;
};

}  // namespace FA
