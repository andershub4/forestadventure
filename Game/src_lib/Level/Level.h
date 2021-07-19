/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Camera.h"
#include "Entity/EntityManager.h"
#include "Fwd/SfmlFwd.h"
#include "Resource/AnimationManager.h"
#include "Tile/TileMap.h"

namespace FA {

namespace Entity {
class BasicEntity;
}

class TextureManager;
class MessageBus;

class Level
{
public:
    Level(MessageBus& messageBus, sf::RenderTarget& renderTarget, TextureManager& textureManager);
    ~Level();

    void Update(float deltaTime);
    void Draw();

    void Load(const std::string& mapPath);
    void EnableInput(bool enable);

private:
    static const unsigned int scale_{2};

    sf::RenderTarget& renderTarget_;
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    AnimationManager animationManager_;
    Entity::EntityManager entityManager_;
    Tile::TileMap tileMap_;
    Camera camera_;
};

}  // namespace FA
