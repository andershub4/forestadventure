/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class BasicSprite
{
public:
    virtual ~BasicSprite() = default;
    
    virtual void Enter() = 0;
    virtual void Update(float deltaTime) = 0;

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void DrawTo(sf::RenderTarget &renderTarget);

protected:
    sf::Sprite sprite_;
};

}  // namespace Entity

}  // namespace FA
