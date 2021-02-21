/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "BasicSprite.h"

namespace FA {

namespace Entity {

class StaticSprite : public BasicSprite
{
public:
    StaticSprite(unsigned int size, const sf::Vector2u& position, const sf::Texture* texture, const sf::IntRect& rect);
    virtual ~StaticSprite();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual sf::Vector2f GetPosition() const override;
    virtual void Move(const Movement& movement) override;

private:
    sf::RectangleShape rectShape_;
};

}  // namespace Entity

}  // namespace FA
