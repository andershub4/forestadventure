/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity/Factory.h"
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
    Level(const Tile::TileMapData& tileMapData, TextureManager& textureManager);
    ~Level();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);

    void Create(Camera& camera, MessageBus& messageBus);
    void EnableInput(bool enable);
    sf::Vector2u GetSize() const;

private:
    static const unsigned int scale_{2};

    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    AnimationManager animationManager_;
    EntitySystem entitySystem_;
    Tile::TileMap tileMap_;
    Entity::Factory factory_;
};

}  // namespace FA
