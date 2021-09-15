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
#include "Resource/AnimationDb.h"
#include "Tile/TileMap.h"

namespace FA {

class MessageBus;

class Level
{
public:
    Level(MessageBus& messageBus, sf::RenderTarget& renderTarget, const Tile::TileMap& tileMap,
          const AnimationDb& animationDb);
    ~Level();

    void Update(float deltaTime);
    void Draw();

    void Create();
    void EnableInput(bool enable);

private:
    sf::RenderTarget& renderTarget_;
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    Entity::Factory factory_;
    Entity::EntityManager entityManager_;
    Tile::TileMap tileMap_;
    CameraManager cameraManager_;
    AnimationDb animationDb_;
};

}  // namespace FA
