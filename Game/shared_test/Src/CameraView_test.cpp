/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <tuple>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>

#include "CameraView.h"

using namespace testing;

namespace FA {

namespace Shared {

class CameraViewTest : public testing::Test
{
protected:
    sf::Vector2u viewSize_{20u, 20u};
    sf::Vector2u mapSize_{100u, 100u};
};

TEST_F(CameraViewTest, GetPositionShouldReturnDefaultPositionWhenPointNotIsSet)
{
    CameraView cameraView(viewSize_, mapSize_, 1.0f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(0.0f, 0.0f)));

    cameraView.UpdatePosition(0.01f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(0.0f, 0.0f)));
}
TEST_F(CameraViewTest, GetPositionShouldReturnInitPositionWhenTrackPointIsSet)
{
    CameraView cameraView(viewSize_, mapSize_, 1.0f);
    sf::Vector2f point(50u, 50u);
    cameraView.SetTrackPoint(point);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(50.0f, 50.0f)));

    cameraView.UpdatePosition(0.01f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(50.0f, 50.0f)));
}

TEST_F(CameraViewTest, GetPositionShouldReturnUpdatedPositionWhenPointIsTrackedAndUpdated)
{
    CameraView cameraView(viewSize_, mapSize_, 1.0f);
    sf::Vector2f point(50u, 50u);
    cameraView.SetTrackPoint(point);
    point.x += 5.0f;

    cameraView.UpdatePosition(0.01f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(55.0f, 50.0f)));

    point.y += 2.0f;
    cameraView.UpdatePosition(0.01f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(55.0f, 52.0f)));
}

TEST_F(CameraViewTest, GetPositionShouldReturnInitPositionWhenPointIsFixedAndUpdated)
{
    CameraView cameraView(viewSize_, mapSize_, 1.0f);
    sf::Vector2f point(50u, 50u);
    cameraView.SetFixPoint(point);
    point.x += 5.0f;

    cameraView.UpdatePosition(0.01f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(50.0f, 50.0f)));

    point.y += 2.0f;
    cameraView.UpdatePosition(0.01f);
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(50.0f, 50.0f)));
}

struct PositionItem
{
    sf::Vector2f input;
    sf::Vector2f expected;
};

class CameraViewAdjustmentTestP : public CameraViewTest, public WithParamInterface<PositionItem>
{
};

INSTANTIATE_TEST_CASE_P(CameraViewTests, CameraViewAdjustmentTestP,
                        Values(
                            /* ---------- Upper left corner ---------- */
                            PositionItem{{10.0f, 10.0f}, {10.0f, 10.0f}},  // view fit inside map -> no adjustment
                            PositionItem{{1.0f, 10.0f}, {10.0f, 10.0f}},   // view does not fit -> x adjustment
                            PositionItem{{10.0f, 1.0f}, {10.0f, 10.0f}},   // view does not fit -> y adjustment
                            PositionItem{{1.0f, 1.0f}, {10.0f, 10.0f}},    // view does not fit -> x, y adjustment
                            /* ---------- Upper right corner ---------- */
                            PositionItem{{90.0f, 10.0f}, {90.0f, 10.0f}},  // view fit inside map -> no adjustment
                            PositionItem{{99.0f, 10.0f}, {90.0f, 10.0f}},  // view does not fit -> x adjustment
                            PositionItem{{90.0f, 1.0f}, {90.0f, 10.0f}},   // view does not fit -> y adjustment
                            PositionItem{{99.0f, 1.0f}, {90.0f, 10.0f}},   // view does not fit -> x, y adjustment
                            /* ---------- Lower right corner ---------- */
                            PositionItem{{90.0f, 90.0f}, {90.0f, 90.0f}},  // view fit inside map -> no adjustment
                            PositionItem{{99.0f, 90.0f}, {90.0f, 90.0f}},  // view does not fit -> x adjustment
                            PositionItem{{90.0f, 99.0f}, {90.0f, 90.0f}},  // view does not fit -> y adjustment
                            PositionItem{{99.0f, 99.0f}, {90.0f, 90.0f}},  // view does not fit -> x, y adjustment
                            /* ---------- Lower left corner ---------- */
                            PositionItem{{10.0f, 90.0f}, {10.0f, 90.0f}},   // view fit inside map -> no adjustment
                            PositionItem{{1.0f, 90.0f}, {10.0f, 90.0f}},    // view does not fit -> x adjustment
                            PositionItem{{10.0f, 99.0f}, {10.0f, 90.0f}},   // view does not fit -> y adjustment
                            PositionItem{{1.0f, 99.0f}, {10.0f, 90.0f}}));  // view does not fit -> x, y adjustment

TEST_P(CameraViewAdjustmentTestP, GetPositionShouldReturnAdjustedPositionWhenPointCauseViewOutsideMap)
{
    CameraView cameraView(viewSize_, mapSize_, 1.0f);
    const auto &item = GetParam();
    sf::Vector2f point = item.input;
    sf::Vector2f expected = item.expected;

    cameraView.SetTrackPoint(point);
    EXPECT_THAT(cameraView.GetPosition(), Eq(expected));

    cameraView.SetFixPoint(point);
    EXPECT_THAT(cameraView.GetPosition(), Eq(expected));
}

class CameraViewZoomAdjustmentTestP : public CameraViewTest, public WithParamInterface<std::tuple<float, sf::Vector2f>>
{
};

INSTANTIATE_TEST_CASE_P(CameraViewZoomTests, CameraViewZoomAdjustmentTestP,
                        Values(std::make_tuple(1.0f, sf::Vector2f(10.0f, 10.0f)),
                               std::make_tuple(0.5f, sf::Vector2f(5.0f, 5.0f)),
                               std::make_tuple(2.0f, sf::Vector2f(20.0f, 20.0f))));

TEST_P(CameraViewZoomAdjustmentTestP, GetPositionShouldReturnAdjustedPositionWhenPointCauseViewOutsideMap)
{
    const auto &item = GetParam();
    float zoomFactor = std::get<0>(item);
    sf::Vector2f expected = std::get<1>(item);
    CameraView cameraView(viewSize_, mapSize_, zoomFactor);

    sf::Vector2f point{1.0f, 1.0f};
    cameraView.SetTrackPoint(point);
    EXPECT_THAT(cameraView.GetPosition(), Eq(expected));

    cameraView.SetFixPoint(point);
    EXPECT_THAT(cameraView.GetPosition(), Eq(expected));
}

class CameraViewRangeTestP : public CameraViewTest, public WithParamInterface<std::tuple<float, float>>
{
};

INSTANTIATE_TEST_CASE_P(CameraViewTests2, CameraViewRangeTestP, Combine(Range(0.0f, 4.0f), Range(0.0f, 4.0f)));

TEST_P(CameraViewRangeTestP, GetPositionShouldAlwaysReturnCenterPointWhenViewAndMapSizesAreEqual)
{
    CameraView cameraView({4u, 4u}, {4u, 4u}, 1.0f);
    float x = std::get<0>(GetParam());
    float y = std::get<1>(GetParam());
    cameraView.SetTrackPoint({x, y});
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(2.0f, 2.0f)));

    cameraView.SetFixPoint({x, y});
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(2.0f, 2.0f)));
}

TEST_P(CameraViewRangeTestP, GetPositionShouldAlwaysReturnCenterPointWhenViewSizeIsLargerThanMapSize)
{
    CameraView cameraView({16u, 16u}, {4u, 4u}, 1.0f);
    float x = std::get<0>(GetParam());
    float y = std::get<1>(GetParam());
    cameraView.SetTrackPoint({x, y});
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(8.0f, 8.0f)));

    cameraView.SetFixPoint({x, y});
    EXPECT_THAT(cameraView.GetPosition(), Eq(sf::Vector2f(8.0f, 8.0f)));
}

}  // namespace Shared

}  // namespace FA
