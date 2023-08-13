/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "CameraManager.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Entity {

class EntityManager;

}  // namespace Entity

namespace Shared {

class MessageBus;

}  // namespace Shared

namespace World {

class LevelCreator;
class TileMap;

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

private:
    const sf::Vector2u viewSize_;
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    Shared::TextureManager& textureManager_;
    Shared::SheetManager sheetManager_;
    std::unique_ptr<TileMap> tileMap_;
    Shared::CameraManager cameraManager_;
    std::unique_ptr<Entity::EntityManager> entityManager_;
    std::unique_ptr<LevelCreator> levelCreator_;

private:
    void LoadEntitySheets();
    void LoadTileMap(const std::string& levelName);
    void CreateMap();
    void CreateEntities();
};

}  // namespace World

}  // namespace FA
