/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include <SFML/System/Vector2.hpp>

#include "ITexture.h"

namespace FA {

namespace Graphic {

class TextureMock : public ITexture
{
public:
    MOCK_METHOD((bool), create, (unsigned int, unsigned int), (override));

    MOCK_METHOD((bool), loadFromFile, (const std::string&), (override));
    MOCK_METHOD((bool), loadFromFile, (const std::string&, const sf::IntRect&), (override));

    MOCK_METHOD((bool), loadFromMemory, (const void*, std::size_t), (override));
    MOCK_METHOD((bool), loadFromMemory, (const void*, std::size_t, const sf::IntRect&), (override));

    MOCK_METHOD((sf::Vector2u), getSize, (), (const override));
};

}  // namespace Graphic

}  // namespace FA
