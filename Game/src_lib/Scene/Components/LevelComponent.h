/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "BasicComponent.h"
#include "Entity/Id.h"
#include "Level/Camera.h"
#include "Resource/AnimationManager.h"
#include "Resource/TileSet.h"
#include "Tile/TileMap.h"

namespace FA {

namespace Entity {
class BasicEntity;
}

class TextureManager;
class BasicEffect;

namespace Scene {

class LevelComponent : public BasicComponent
{
public:
    LevelComponent(MessageBus& messageBus, TextureManager& textureManager);
    virtual ~LevelComponent();

    virtual ComponentId GetId() const override { return ComponentId::Level; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override;
    virtual void EnterTransition(const BasicTransition& transition) override;
    virtual void ExitTransition(const BasicTransition& transition) override;

private:
    AnimationManager animationManager_;
    TileSet tileSet_;
    std::unique_ptr<Entity::BasicEntity> entity_;
    std::unique_ptr<Entity::BasicEntity> moleEntity_;
    std::unique_ptr<Entity::BasicEntity> stoneEntity_;
    Tile::TileMap tileMap_;
    Camera camera_;
    std::unique_ptr<BasicEffect> effect_ = nullptr;
    Entity::EntityId entityId_ = 0;

private:
    Entity::EntityId GenerateEntityId();
};

}  // namespace Scene

}  // namespace FA
