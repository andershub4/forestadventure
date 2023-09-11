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

TEST(ImageSpriteTest, ImageSpriteShouldUpdateTexture)
{
    auto spriteMock = std::make_shared<StrictMock<Graphic::SpriteMock>>();
    Graphic::TextureMock textureMock;
    sf::IntRect rect{0, 0, 10, 12};
    Frame frame{&textureMock, rect};
    ImageSprite sprite(spriteMock, frame);
    EXPECT_CALL(*spriteMock, setTextureImpl(Address(&textureMock), false));
    EXPECT_CALL(*spriteMock, setTextureRect(Eq(rect)));
    sprite.Update(0.1f);
}

}  // namespace Shared

}  // namespace FA
