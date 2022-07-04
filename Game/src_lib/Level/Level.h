/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "CameraManager.h"
#include "Entity/EntityManager.h"
#include "Entity/Factory.h"
#include "Fwd/SfmlFwd.h"
#include "Tile/TileMap.h"

namespace FA {

class MessageBus;

class Level
{
public:
    Level(MessageBus& messageBus, const Tile::TileMap& tileMap, const SheetManager& sheetManager,
          const sf::Vector2u& viewSize);
    ~Level();

    void Update(float deltaTime);
    void Draw(sf::RenderTarget& renderTarget);

    void Create();
    sf::View GetView();

private:
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    const Tile::TileMap& tileMap_;
    CameraManager cameraManager_;
    Entity::Factory factory_;
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
