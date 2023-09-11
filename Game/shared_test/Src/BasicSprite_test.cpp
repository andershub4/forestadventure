/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SpriteMock.h"
#include "Sprites/BasicSprite.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(BasicSpriteTest, BasicSpriteShouldSetPosition)
{
    auto spriteMock = std::make_shared<StrictMock<Graphic::SpriteMock>>();
    sf::Vector2f pos{12.0f, 3.0f};
    BasicSprite sprite(spriteMock);
    EXPECT_CALL(*spriteMock, setPosition(Eq(pos)));
    sprite.SetPosition(pos);
}

}  // namespace Shared

}  // namespace FA
