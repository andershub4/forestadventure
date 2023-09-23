/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>

#include "RenderTargetMock.h"
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

TEST(BasicSpriteTest, BasicSpriteShouldSetRotation)
{
    auto spriteMock = std::make_shared<StrictMock<Graphic::SpriteMock>>();
    float rot = 32.0f;
    BasicSprite sprite(spriteMock);
    EXPECT_CALL(*spriteMock, setRotation(Eq(rot)));
    sprite.SetRotation(rot);
}

TEST(BasicSpriteTest, BasicSpriteShouldDrawTo)
{
    auto spriteMock = std::make_shared<StrictMock<Graphic::SpriteMock>>();
    Graphic::RenderTargetMock renderTargetMock;
    BasicSprite sprite(spriteMock);
    EXPECT_CALL(renderTargetMock, draw(Ref(*spriteMock)));
    sprite.DrawTo(renderTargetMock);
}

TEST(BasicSpriteTest, BasicSpriteShouldCenter)
{
    auto spriteMock = std::make_shared<StrictMock<Graphic::SpriteMock>>();
    BasicSprite sprite(spriteMock);
    sf::FloatRect rect{10.0f, 12.0f, 30.0f, 10.0f};
    EXPECT_CALL(*spriteMock, getLocalBounds()).WillRepeatedly(Return(rect));
    EXPECT_CALL(*spriteMock, setOrigin(Eq(15.0f), Eq(5.0f)));
    sprite.Center();
}

}  // namespace Shared

}  // namespace FA
