/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "Animation/ImageAnimation.h"
#include "CameraViews.h"
#include "Id.h"
#include "RenderTexture.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureManager.h"
#include "SfmlFwd.h"
#include "Sprite.h"

namespace FA {

namespace Graphic {

class View;

}  // namespace Graphic

namespace Entity {

class Factory;
class EntityDb;
class EntityLifePool;
class CollisionHandler;
class DrawHandler;

}  // namespace Entity

namespace Shared {

class MessageBus;
struct EntityData;

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
    void Draw(Graphic::RenderTargetIf& renderTarget);

    void Create();
    Graphic::View GetView() const;

private:
    const sf::Vector2u viewSize_;
    Graphic::RenderTexture backgroundTexture_;
    Graphic::Sprite backgroundSprite_;
    std::vector<Graphic::Sprite> fringeLayer_;
    std::vector<Shared::ImageAnimation> animationLayer_;
    Shared::MessageBus& messageBus_;
    Shared::TextureManager& textureManager_;
    Shared::SheetManager sheetManager_;
    std::unique_ptr<TileMap> tileMap_;
    Shared::CameraViews cameraViews_;
    std::unordered_set<Entity::EntityId> allEntities_;
    std::unique_ptr<Entity::Factory> factory_;
    std::unique_ptr<Entity::EntityDb> entityDb_;
    std::unique_ptr<Entity::CollisionHandler> collisionHandler_;
    std::unique_ptr<Entity::DrawHandler> drawHandler_;
    std::unique_ptr<Entity::EntityLifePool> entityLifePool_;
    std::unique_ptr<LevelCreator> levelCreator_;
    const float zoomFactor_{0.4f};

private:
    void LoadEntitySheets();
    void LoadTileMap(const std::string& levelName);
    void CreateMap();
    void CreateEntities();
    void HandleCreation(const Shared::EntityData& data);
    void HandleDeletion(Entity::EntityId id);
};

}  // namespace World

}  // namespace FA
