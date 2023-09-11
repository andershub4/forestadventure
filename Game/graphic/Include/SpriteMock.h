/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include <SFML/Graphics/Rect.hpp>

#include "ISprite.h"

namespace FA {

namespace Graphic {

class SpriteMock : public ISprite
{
public:
    MOCK_METHOD((void), setTextureImpl, (const ITexture&, bool));
    virtual void setTexture(const ITexture& texture, bool resetRect = false) override
    {
        return setTextureImpl(texture, resetRect);
    }
    MOCK_METHOD((void), setTextureRect, (const sf::IntRect&), (override));
    MOCK_METHOD((void), setColor, (const sf::Color&), (override));
    MOCK_METHOD((const ITexture*), getTexture, (), (const));
    MOCK_METHOD((sf::FloatRect), getLocalBounds, (), (const override));
    MOCK_METHOD((void), setPosition, (float, float), (override));
    MOCK_METHOD((void), setPosition, (const sf::Vector2f&), (override));
    MOCK_METHOD((void), setRotation, (float), (override));

    MOCK_METHOD((void), setOrigin, (float, float), (override));

private:
    MOCK_METHOD((const sf::Drawable&), conversionOperator, (), (const));
    virtual operator const sf::Drawable&() const { return conversionOperator(); }
};

// sf::Sprite SpriteMock::sprite_;

}  // namespace Graphic

}  // namespace FA
