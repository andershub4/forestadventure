/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "RectangleShapeIf.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RectangleShapeMock : public RectangleShapeIf
{
public:
    MOCK_METHOD((sf::FloatRect), getLocalBounds, (), (const override));
    MOCK_METHOD((sf::FloatRect), getGlobalBounds, (), (const override));
    MOCK_METHOD((void), setSize, (const sf::Vector2f &), (override));
    MOCK_METHOD((void), setPosition, (float, float), (override));
    MOCK_METHOD((void), setPosition, (const sf::Vector2f &), (override));
    MOCK_METHOD((void), setRotation, (float), (override));
    MOCK_METHOD((void), setFillColor, (const sf::Color &), (override));
    MOCK_METHOD((void), setOutlineColor, (const sf::Color &), (override));
    MOCK_METHOD((void), setOutlineThickness, (float), (override));
    MOCK_METHOD((void), setOrigin, (float, float), (override));

private:
    MOCK_METHOD((const sf::Drawable &), conversionOperator, (), (const));
    virtual operator const sf::Drawable &() const { return conversionOperator(); }
};

}  // namespace Graphic

}  // namespace FA
