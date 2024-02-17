/*
 *	Copyright (C) 2024 Anders Wennmo
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
#include "Sprites/SpriteIf.h"

using namespace testing;

namespace FA {

namespace Shared {

class BasicSpriteTest : public testing::Test
{
protected:
    BasicSpriteTest()
        : spriteMock_(std::make_shared<StrictMock<Graphic::SpriteMock>>())
        , sprite_(spriteMock_)
    {}

protected:
    std::shared_ptr<StrictMock<Graphic::SpriteMock>> spriteMock_;
    BasicSprite<SpriteIf> sprite_;
};

TEST_F(BasicSpriteTest, BasicSpriteShouldSetPosition)
{
    sf::Vector2f pos{12.0f, 3.0f};
    EXPECT_CALL(*spriteMock_, setPosition(Eq(pos)));
    sprite_.SetPosition(pos);
}

TEST_F(BasicSpriteTest, BasicSpriteShouldSetRotation)
{
    float rot = 32.0f;
    EXPECT_CALL(*spriteMock_, setRotation(Eq(rot)));
    sprite_.SetRotation(rot);
}

TEST_F(BasicSpriteTest, BasicSpriteShouldDrawTo)
{
    Graphic::RenderTargetMock renderTargetMock;
    EXPECT_CALL(renderTargetMock, draw(Ref(*spriteMock_)));
    sprite_.DrawTo(renderTargetMock);
}

TEST_F(BasicSpriteTest, BasicSpriteShouldCenter)
{
    sf::FloatRect rect{10.0f, 12.0f, 30.0f, 10.0f};
    EXPECT_CALL(*spriteMock_, getLocalBounds()).WillRepeatedly(Return(rect));
    EXPECT_CALL(*spriteMock_, setOrigin(Eq(15.0f), Eq(5.0f)));
    sprite_.Center();
}

}  // namespace Shared

}  // namespace FA
