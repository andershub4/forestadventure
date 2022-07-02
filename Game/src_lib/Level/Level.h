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
#include "Resource/SheetManager.h"
#include "Resource/TextureManager.h"
#include "Tile/TileMap.h"

namespace FA {

class MessageBus;
class CameraManager;

class Level
{
public:
    Level(MessageBus& messageBus, TextureManager& textureManager, CameraManager& cameraManager);
    ~Level();

    void Update(float deltaTime);
    void Draw(sf::RenderTarget& renderTarget);

    void Load();
    void Setup();
    sf::Vector2u GetMapSize() const;

private:
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    Entity::Factory factory_;
    SheetManager sheetManager_;
    Tile::TileMap tileMap_;
    Entity::EntityManager entityManager_;

private:
    void CreateBackground();
    void CreateEntities();
    void CreateFringe();

    void CreateBackgroundTile(const Tile::TileMap::TileData& data);
    void CreateTileEntity(const Tile::TileMap::TileData& data);
    void CreateFringeTile(const Tile::TileMap::TileData& data);
    void CreateObjectEntity(const Tile::TileMap::ObjectData& data);
};

}  // namespace FA
