/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Animation/AnimationFactory.h"
#include "BasicComponent.h"
#include "Tile/TileMap.h"

namespace FA {

namespace Entity {

class BasicEntity;

}

class TextureManager;

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

private:
    AnimationFactory animationFactory_;
    std::unique_ptr<Entity::BasicEntity> entity_;
    Tile::TileMap tileMap_;
    sf::View view_;

private:
    void RegisterAnimationInfo(TextureManager& textureManager);
    sf::Vector2f CalcViewPosition(const sf::Vector2f& position) const;
};

}  // namespace Scene

}  // namespace FA
