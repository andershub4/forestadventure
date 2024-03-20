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
#include "Sprites/BasicCoolSprite.h"
#include "Sprites/CoolSpriteIf.h"

using namespace testing;

namespace FA {

namespace Shared {

class BasicCoolSpriteTest : public testing::Test
{
protected:
    BasicCoolSpriteTest()
        : spriteMock_(std::make_shared<StrictMock<Graphic::SpriteMock>>())
        , sprite_(spriteMock_)
    {}

protected:
    std::shared_ptr<StrictMock<Graphic::SpriteMock>> spriteMock_;
    BasicCoolSprite<CoolSpriteIf> sprite_;
};

TEST_F(BasicCoolSpriteTest, BasicSpriteShouldSetPosition)
{
    sf::Vector2f pos{12.0f, 3.0f};
    EXPECT_CALL(*spriteMock_, setPosition(Eq(pos)));
    sprite_.SetPosition(pos);
}

TEST_F(BasicCoolSpriteTest, BasicSpriteShouldSetRotation)
{
    float rot = 32.0f;
    EXPECT_CALL(*spriteMock_, setRotation(Eq(rot)));
    sprite_.SetRotation(rot);
}

TEST_F(BasicCoolSpriteTest, BasicSpriteShouldDrawTo)
{
    Graphic::RenderTargetMock renderTargetMock;
    EXPECT_CALL(renderTargetMock, draw(Ref(*spriteMock_)));
    sprite_.DrawTo(renderTargetMock);
}

TEST_F(BasicCoolSpriteTest, BasicSpriteShouldCenter)
{
    sf::FloatRect rect{10.0f, 12.0f, 30.0f, 10.0f};
    EXPECT_CALL(*spriteMock_, getLocalBounds()).WillRepeatedly(Return(rect));
    EXPECT_CALL(*spriteMock_, setOrigin(Eq(15.0f), Eq(5.0f)));
    sprite_.Center();
}

}  // namespace Shared

}  // namespace FA
