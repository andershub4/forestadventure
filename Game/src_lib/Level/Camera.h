/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/View.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {
class BasicEntity;
}

class Camera
{
public:
    Camera(const sf::Vector2u& size);
    ~Camera();

    void UpdatePosition(sf::RenderTarget& renderTarget, const sf::Vector2u& mapSize);
    void Follow(Entity::BasicEntity* entity);

private:
    Entity::BasicEntity* entity_ = nullptr;
    sf::View view_;
    sf::Vector2f centerPos_;

private:
    sf::Vector2f CalcViewPosition(const sf::Vector2f& position, const sf::Vector2u& mapSize) const;
};

}  // namespace FA
