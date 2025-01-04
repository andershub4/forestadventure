/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Animation/ImageTraits.h"
#include "Resource/ImageFrame.h"
#include "SpriteMock.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(ImageTraitsTest, ApplyShouldSetTexture)
{
    StrictMock<Graphic::SpriteMock> spriteMock;
    StrictMock<Graphic::TextureMock> textureMock;
    sf::IntRect rect{0, 0, 10, 20};
    sf::Vector2f center{5.0f, 10.0f};
    ImageFrame frame{&textureMock, rect, center};
    EXPECT_CALL(spriteMock, setTextureImpl(_, _));
    EXPECT_CALL(spriteMock, setTextureRect(Eq(rect)));
    AnimationTraits<ImageFrame>::Apply(frame, spriteMock, false);
}

TEST(ImageTraitsTest, ApplyWithCenterShouldSetSizeAndCenter)
{
    StrictMock<Graphic::SpriteMock> spriteMock;
    StrictMock<Graphic::TextureMock> textureMock;
    sf::IntRect rect{0, 0, 10, 20};
    sf::Vector2f center{5.0f, 10.0f};
    ImageFrame frame{&textureMock, rect, center};
    EXPECT_CALL(spriteMock, setTextureImpl(_, _));
    EXPECT_CALL(spriteMock, setTextureRect(Eq(rect)));
    EXPECT_CALL(spriteMock, setOrigin(Eq(center.x), Eq(center.y)));
    AnimationTraits<ImageFrame>::Apply(frame, spriteMock, true);
}

}  // namespace Shared

}  // namespace FA
