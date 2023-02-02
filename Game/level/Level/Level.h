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
#include "Entity/Id.h"
#include "Entity/SpawnManager.h"
#include "Fwd/SfmlFwd.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureManager.h"
#include "TileMap.h"

namespace FA {

namespace Shared {

class MessageBus;

}  // namespace Shared

class Level
{
public:
    Level(Shared::MessageBus& messageBus, Shared::TextureManager& textureManager, const sf::Vector2u& viewSize);
    ~Level();

    void Load(const std::string& levelName);
    void Update(float deltaTime);
    void Draw(sf::RenderTarget& renderTarget);

    void Create();
    sf::View GetView();
    void SpawnEntity(EntityType entityType, MoveDirection moveDirection, const sf::Vector2f& position);
    void DeleteEntity(Entity::EntityId id);
    sf::FloatRect GetMapRect() const;

private:
    const sf::Vector2u viewSize_;
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    Shared::SheetManager sheetManager_;
    TileMap tileMap_;
    CameraManager cameraManager_;
    Entity::Factory factory_;
    Entity::EntityManager entityManager_;
    sf::FloatRect mapRect_{};
    Entity::SpawnManager spawnManager_;

private:
    void LoadEntitySheets();
    void LoadTileMap(const std::string& levelName);

    void CreateBackground();
    void CreateEntities();
    void CreateFringe();

    void CreateBackgroundTile(const TileMap::TileData& data);
    void CreateTileEntity(const TileMap::TileData& data);
    void CreateFringeTile(const TileMap::TileData& data);
    void CreateObjectEntity(const TileMap::ObjectData& data);
};

}  // namespace FA
