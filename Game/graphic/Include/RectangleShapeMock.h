/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "RectangleShapeIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RectangleShapeMock : public RectangleShapeIf
{
public:
    MOCK_METHOD((sf::FloatRect), getLocalBounds, (), (const override));
    MOCK_METHOD((sf::FloatRect), getGlobalBounds, (), (const override));
    MOCK_METHOD((void), setSize, (const sf::Vector2f &size), (override));
    MOCK_METHOD((void), setPosition, (float x, float y), (override));
    MOCK_METHOD((void), setPosition, (const sf::Vector2f &position), (override));
    MOCK_METHOD((void), setRotation, (float angle), (override));
    MOCK_METHOD((void), setFillColor, (const sf::Color &color), (override));
    MOCK_METHOD((void), setOutlineColor, (const sf::Color &color), (override));
    MOCK_METHOD((void), setOutlineThickness, (float thickness), (override));
    MOCK_METHOD((void), setOrigin, (float x, float y), (override));

private:
    MOCK_METHOD((const sf::Drawable &), conversionOperator, (), (const));
    virtual operator const sf::Drawable &() const { return conversionOperator(); }
};

}  // namespace Graphic

}  // namespace FA
