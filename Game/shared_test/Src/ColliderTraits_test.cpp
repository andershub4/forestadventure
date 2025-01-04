/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Animation/ColliderTraits.h"
#include "RectangleShapeMock.h"
#include "Resource/ColliderFrame.h"

using namespace testing;

namespace FA {

namespace Shared {

TEST(ColliderTraitsTest, ApplyShouldSetSize)
{
    StrictMock<Graphic::RectangleShapeMock> rectMock;
    sf::Vector2f size{10.0f, 10.0f};
    sf::Vector2f center{5.0f, 5.0f};
    ColliderFrame frame{size, center};
    EXPECT_CALL(rectMock, setSize(Eq(size)));
    AnimationTraits<ColliderFrame>::Apply(frame, rectMock, false);
}

TEST(ColliderTraitsTest, ApplyWithCenterShouldSetSizeAndCenter)
{
    StrictMock<Graphic::RectangleShapeMock> rectMock;
    sf::Vector2f size{10.0f, 10.0f};
    sf::Vector2f center{5.0f, 5.0f};
    ColliderFrame frame{size, center};
    EXPECT_CALL(rectMock, setSize(Eq(size)));
    EXPECT_CALL(rectMock, setOrigin(Eq(center.x), Eq(center.y)));
    AnimationTraits<ColliderFrame>::Apply(frame, rectMock, true);
}

}  // namespace Shared

}  // namespace FA
