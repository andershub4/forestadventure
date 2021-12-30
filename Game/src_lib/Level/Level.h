/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity/EntityManager.h"
#include "Entity/Factory.h"
#include "Fwd/SfmlFwd.h"
#include "Tile/TileMap.h"

namespace FA {

class MessageBus;
class CameraManager;

class Level
{
public:
    Level(MessageBus& messageBus, TextureManager& textureManager);
    ~Level();

    void Update(float deltaTime);
    void Draw(sf::RenderTarget& renderTarget);

    void Load();
    void Create(CameraManager& cameraManager);
    void EnableInput(bool enable);
    sf::Vector2u GetMapSize() const;

private:
    static const unsigned int scale_{2};

    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    Entity::Factory factory_;
    Entity::EntityManager entityManager_;
    Tile::TileMap tileMap_;
    TextureManager& textureManager_;
};

}  // namespace FA
