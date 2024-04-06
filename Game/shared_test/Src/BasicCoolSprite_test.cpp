/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Sprites/BasicCoolSprite.h"
#include "Sprites/CoolSpriteIf.h"

using namespace testing;

namespace FA {

namespace Shared {

// Currently, there are no common methods for the sprite classes,
// but I've decided to keep this file in case there will be
// new methods in future, and also keep it as a code reference
// when dealing with multiple sub classes and mocks.
class BasicCoolSpriteTest : public testing::Test
{
    BasicCoolSprite<CoolSpriteIf> sprite_;
};

TEST_F(BasicCoolSpriteTest, Test1)
{}

}  // namespace Shared

}  // namespace FA
