/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SpriteMock.h"
#include "Sprites/ImageSprite.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class ImageSpriteTest : public testing::Test
{
protected:
    ImageSpriteTest()
        : spriteMock_(std::make_shared<StrictMock<Graphic::SpriteMock>>())
        , sprite_(spriteMock_, frame_)
    {}

protected:
    Graphic::TextureMock textureMock_;
    sf::IntRect rect_{0, 0, 10, 12};
    Frame frame_{&textureMock_, rect_};
    std::shared_ptr<StrictMock<Graphic::SpriteMock>> spriteMock_;
    ImageSprite sprite_;
};
TEST_F(ImageSpriteTest, UpdateShouldSetTexture)
{
    EXPECT_CALL(*spriteMock_, setTextureImpl(Address(&textureMock_), false));
    EXPECT_CALL(*spriteMock_, setTextureRect(Eq(rect_)));

    sprite_.Update(0.1f);
}

TEST_F(ImageSpriteTest, UpdateWithInvalidTextureShouldNotSetTexture)
{
    Frame frame{nullptr, rect_};
    ImageSprite sprite(spriteMock_, frame);

    sprite.Update(0.1f);
}

TEST_F(ImageSpriteTest, UpdateWithInvalidWidthShouldNotSetTexture)
{
    sf::IntRect rect{0, 0, 0, 12};
    Frame frame{&textureMock_, rect};
    ImageSprite sprite(spriteMock_, frame);

    sprite.Update(0.1f);
}

TEST_F(ImageSpriteTest, UpdateWithInvalidHeightShouldNotSetTexture)
{
    sf::IntRect rect{0, 0, 10, 0};
    Frame frame{&textureMock_, rect};
    ImageSprite sprite(spriteMock_, frame);

    sprite.Update(0.1f);
}

}  // namespace Shared

}  // namespace FA
