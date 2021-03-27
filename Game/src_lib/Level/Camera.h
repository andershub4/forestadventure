/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/View.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class Level;

namespace Entity {
class BasicEntity;
}

class Camera
{
public:
    Camera(const Level &level);
    ~Camera();

    void UpdatePosition(sf::RenderTarget& renderTarget);
    void Follow(Entity::BasicEntity* entity);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetViewSize() const;

private:
    Entity::BasicEntity* entity_ = nullptr;
    sf::View view_;
    const Level& level_;

private:
    sf::Vector2f CalcViewPosition(const sf::Vector2f& position) const;
};

}  // namespace FA
