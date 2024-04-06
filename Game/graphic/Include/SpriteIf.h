/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "DrawableIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class TextureIf;

class SpriteIf : public DrawableIf
{
public:
    virtual void setTexture(const TextureIf &texture, bool resetRect = false) = 0;
    virtual void setTextureRect(const sf::IntRect &rectangle) = 0;
    virtual void setColor(const sf::Color &color) = 0;
    virtual const TextureIf *getTexture() const = 0;

    virtual sf::FloatRect getLocalBounds() const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    virtual void setRotation(float angle) = 0;

    virtual void setOrigin(float x, float y) = 0;
};

}  // namespace Graphic

}  // namespace FA
