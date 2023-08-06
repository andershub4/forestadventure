/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "ITexture.h"

namespace FA {

namespace Graphic {

class TextureMock : public ITexture
{
public:
    MOCK_METHOD((void), create, (unsigned int width, unsigned int height), (override));

    MOCK_METHOD((bool), loadFromFileImpl, (const std::string& fileName, const sf::IntRect& area));
    virtual bool loadFromFile(const std::string& fileName, const sf::IntRect& area = sf::IntRect()) override
    {
        return loadFromFileImpl(fileName, area);
    }

    MOCK_METHOD((bool), loadFromMemoryImpl, (const void* data, std::size_t size, const sf::IntRect& area));
    virtual bool loadFromMemory(const void* data, std::size_t size, const sf::IntRect& area = sf::IntRect()) override
    {
        return loadFromMemoryImpl(data, size, area);
    }
};

}  // namespace Graphic

}  // namespace FA
