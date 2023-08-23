/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "Resource/SpriteSheetIf.h"

namespace FA {

namespace Shared {

class SpriteSheetMock : public SpriteSheetIf
{
public:
    MOCK_METHOD(std::vector<TextureRect>, Scan, (const sf::Vector2u& uvCoord, unsigned int nRects), (const override));
    MOCK_METHOD(TextureRect, At, (const sf::Vector2u& uvCoord), (const override));
};

class SpriteSheetMockProxy : public SpriteSheetIf
{
public:
    SpriteSheetMockProxy(SpriteSheetMock& mock)
        : mock_(mock)
    {}

    std::vector<TextureRect> Scan(const sf::Vector2u& uvCoord, unsigned int nRects) const override
    {
        return mock_.Scan(uvCoord, nRects);
    }

    TextureRect At(const sf::Vector2u& uvCoord) const override { return mock_.At(uvCoord); }

private:
    SpriteSheetMock& mock_;
};

}  // namespace Shared

}  // namespace FA
