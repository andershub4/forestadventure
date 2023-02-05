/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#ifdef _DEBUG
#include <SFML/Graphics/RectangleShape.hpp>
#endif
#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "Sprites/BasicSprite.h"

namespace FA {

namespace Entity {

struct Body;

class Shape
{
public:
    Shape(Body &body);

    void RegisterSprite(std::shared_ptr<BasicSprite> sprite);
    void Enter();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget);
    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rotation);

private:
    std::vector<std::shared_ptr<BasicSprite>> sprites_;
#ifdef _DEBUG
    sf::RectangleShape rShape_;
#endif
    Body &body_;
};

}  // namespace Entity

}  // namespace FA
