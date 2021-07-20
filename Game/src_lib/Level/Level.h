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
#include "Entity/Factory.h"
#include "Fwd/SfmlFwd.h"
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
    Level(MessageBus& messageBus, TextureManager& textureManager, sf::RenderTarget& renderTarget);
    ~Level();

    void Update(float deltaTime);
    void Draw();

    void Load(const std::string& mapPath);
    void EnableInput(bool enable);

private:
    static const unsigned int scale_{2};

    sf::RenderTarget& renderTarget_;
    TextureManager& textureManager_;
    sf::RenderTexture backgroundTexture_;
    sf::Sprite backgroundSprite_;
    std::vector<sf::Sprite> fringeLayer_;
    Entity::Factory factory_;
    Entity::EntityManager entityManager_;
    Tile::TileMap tileMap_;
    Camera camera_;
};

}  // namespace FA
