/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SFML/System/Vector2.hpp>

#include "CollisionHandlerMock.h"
#include "EntityDbMock.h"
#include "EntityMock.h"
#include "Mock/LoggerMock.h"
#include "SfmlPrint.h"

#include "Grid.h"

using namespace testing;

namespace FA {

namespace Entity {

class Grid100x1000x10Test : public Test
{
protected:
    void SetUp() override
    {
        EXPECT_CALL(entityDbMock_, GetEntity(Eq(movableEntityId1_))).WillRepeatedly(ReturnRef(entityMock1_));
        EXPECT_CALL(entityMock1_, IsStatic).WillRepeatedly(Return(false));

        EXPECT_CALL(entityDbMock_, GetEntity(Eq(movableEntityId2_))).WillRepeatedly(ReturnRef(entityMock2_));
        EXPECT_CALL(entityMock2_, IsStatic).WillRepeatedly(Return(false));

        EXPECT_CALL(entityDbMock_, GetEntity(Eq(staticEntityId1_))).WillRepeatedly(ReturnRef(entityMock3_));
        EXPECT_CALL(entityMock3_, IsStatic).WillRepeatedly(Return(true));
    }

    static constexpr EntityId movableEntityId1_ = 12322;
    static constexpr EntityId movableEntityId2_ = 23212;
    static constexpr EntityId staticEntityId1_ = 44323;

    StrictMock<EntityDbMock> entityDbMock_;
    StrictMock<CollisionHandlerMock> collisionHandlerMock_;
    StrictMock<Shared::LoggerMock> loggerMock_;
    StrictMock<EntityMock> entityMock1_;
    StrictMock<EntityMock> entityMock2_;
    StrictMock<EntityMock> entityMock3_;
    sf::Vector2u mapSize_{100, 100};
    Grid grid_{mapSize_, 10, entityDbMock_, collisionHandlerMock_};
};

TEST_F(Grid100x1000x10Test, AddShouldIncreaseCount)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    EXPECT_EQ(grid_.Count(), 1u);
    grid_.Add(movableEntityId2_, {2.0f, 2.0f}, {2, 2});
    EXPECT_EQ(grid_.Count(), 2u);
}

TEST_F(Grid100x1000x10Test, AddDuplicateShouldLogError)
{
    EXPECT_CALL(entityDbMock_, GetEntity(Eq(1))).WillOnce(ReturnRef(entityMock1_));
    EXPECT_CALL(entityMock1_, IsStatic).WillOnce(Return(false));
    grid_.Add(1, {3.0f, 3.0f}, {2, 2});
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry("{id: 1} already exist"));
    grid_.Add(1, {2.0f, 2.0f}, {2, 2});
    EXPECT_EQ(grid_.Count(), 1u);
}

TEST_F(Grid100x1000x10Test, AddShouldRethrowWhenExceptionIsThrown)
{
    EXPECT_CALL(entityDbMock_, GetEntity(Eq(1))).WillOnce(Throw(std::out_of_range("my error")));
    EXPECT_THROW(grid_.Add(1, {3.0f, 3.0f}, {2, 2}), std::out_of_range);
}

TEST_F(Grid100x1000x10Test, RemoveNonExistingShouldLogError)
{
    EXPECT_CALL(loggerMock_, MakeWarnLogEntry("{id: 1} does not exist"));
    grid_.Remove(1);
}

TEST_F(Grid100x1000x10Test, RemoveShouldDecreaseCount)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(movableEntityId2_, {2.0f, 2.0f}, {2, 2});
    grid_.Remove(movableEntityId1_);
    EXPECT_EQ(grid_.Count(), 1u);
    grid_.Remove(movableEntityId2_);
    EXPECT_EQ(grid_.Count(), 0u);
}

TEST_F(Grid100x1000x10Test, RemoveSmallEntityFromCellWithTwoEntitiesShouldSucceed)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(movableEntityId2_, {2.0f, 2.0f}, {2, 2});
    grid_.Remove(movableEntityId1_);
    EXPECT_EQ(grid_.Count(), 1u);
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions).Times(1);
    grid_.DetectCollisions();
}

TEST_F(Grid100x1000x10Test, RemoveMoveableEntityFromCellWithTwoDifferentEntityTypesShouldSucceed)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(staticEntityId1_, {2.0f, 2.0f}, {2, 2});

    std::unordered_set<EntityId> entities;
    std::unordered_set<EntityId> staticEntities;
    grid_.Remove(movableEntityId1_);
    EXPECT_EQ(grid_.Count(), 1u);
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions(_, _))
        .Times(1)
        .WillOnce(DoAll(SaveArg<0>(&entities), SaveArg<1>(&staticEntities)));
    grid_.DetectCollisions();
    EXPECT_EQ(entities.size(), 0);
    EXPECT_EQ(staticEntities.size(), 1);
}

TEST_F(Grid100x1000x10Test, RemoveStaticEntityFromCellWithTwoDifferentEntityTypesShouldSucceed)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(staticEntityId1_, {2.0f, 2.0f}, {2, 2});

    std::unordered_set<EntityId> entities;
    std::unordered_set<EntityId> staticEntities;
    grid_.Remove(staticEntityId1_);
    EXPECT_EQ(grid_.Count(), 1u);
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions(_, _))
        .Times(1)
        .WillOnce(DoAll(SaveArg<0>(&entities), SaveArg<1>(&staticEntities)));
    grid_.DetectCollisions();
    EXPECT_EQ(entities.size(), 1);
    EXPECT_EQ(staticEntities.size(), 0);
}

TEST_F(Grid100x1000x10Test, RemoveLargeEntityShouldSucceed)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {20, 20});
    grid_.Remove(movableEntityId1_);
    EXPECT_EQ(grid_.Count(), 0u);
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions).Times(0);
    grid_.DetectCollisions();
}

TEST_F(Grid100x1000x10Test, DetectCollisionsWithSmallEntitiesInTwoDifferentCellsShouldAffectTwoCells)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(movableEntityId2_, {71, 71}, {2, 2});
    constexpr unsigned int nAffectedCells = 2;
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions).Times(nAffectedCells);
    grid_.DetectCollisions();
}

TEST_F(Grid100x1000x10Test, DetectCollisionsWithSmallEntitiesInSameCellShouldAffectOneCell)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(movableEntityId2_, {4.0f, 4.0f}, {2, 2});
    constexpr unsigned int nAffectedCells = 1;
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions).Times(nAffectedCells);
    grid_.DetectCollisions();
}

TEST_F(Grid100x1000x10Test, DetectCollisionsWithLargeEntitiesInDifferentCellsShouldAffectSeveralCells)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {20, 20});
    grid_.Add(movableEntityId2_, {23.0f, 23.0f}, {20, 20});
    constexpr unsigned int nAffectedCells = 17;
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions).Times(nAffectedCells);
    grid_.DetectCollisions();
}

TEST_F(Grid100x1000x10Test, DetectCollisionsWithDifferentEntityTypesShouldHaveOneOfEachTypeAsArgument)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Add(staticEntityId1_, {4.0f, 4.0f}, {2, 2});

    std::unordered_set<EntityId> entities;
    std::unordered_set<EntityId> staticEntities;
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions(_, _))
        .WillOnce(DoAll(SaveArg<0>(&entities), SaveArg<1>(&staticEntities)));
    grid_.DetectCollisions();

    EXPECT_EQ(entities.size(), 1);
    EXPECT_EQ(staticEntities.size(), 1);
}

TEST_F(Grid100x1000x10Test, DetectOutsideTileMapShouldBeExectutedForAllMovableEntities)
{
    grid_.Add(movableEntityId1_, {0.0f, 0.0f}, {2, 2});
    grid_.Add(movableEntityId2_, {1.0f, 1.0f}, {2, 2});
    grid_.Add(staticEntityId1_, {3.0f, 3.0f}, {2, 2});
    std::unordered_set<EntityId> entities;
    EXPECT_CALL(collisionHandlerMock_, DetectOutsideTileMap(_, _)).Times(1).WillOnce(SaveArg<1>(&entities));
    grid_.DetectOutsideTileMap();
    EXPECT_EQ(entities.size(), 2);
    EXPECT_THAT(entities, UnorderedElementsAre(movableEntityId1_, movableEntityId2_));
}

TEST_F(Grid100x1000x10Test, MoveFromOneCellToOverlappingCellsShouldAffectTwoCells)
{
    grid_.Add(movableEntityId1_, {3.0f, 3.0f}, {2, 2});
    grid_.Move(movableEntityId1_, {9.0f, 3.0f}, {2, 2});
    constexpr unsigned int nAffectedCells = 2;
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions).Times(nAffectedCells);
    grid_.DetectCollisions();
}

class GridValidEntitySizeTestP : public Grid100x1000x10Test, public WithParamInterface<sf::Vector2u>
{
};

INSTANTIATE_TEST_SUITE_P(ValidEntitySizeTests, GridValidEntitySizeTestP,
                         Values(sf::Vector2u(10, 0), sf::Vector2u(0, 10), sf::Vector2u(0, 0), sf::Vector2u(10, 101),
                                sf::Vector2u(101, 10), sf::Vector2u(101, 101)));

TEST_P(GridValidEntitySizeTestP, AddInvalidEntitySizeShouldLogError)
{
    const auto &size = GetParam();
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("invalid size")));
    grid_.Add(1, {1.0f, 1.0f}, size);
    EXPECT_EQ(grid_.Count(), 0u);
}

class GridValidEntityPositionTestP : public Grid100x1000x10Test, public WithParamInterface<sf::Vector2f>
{
};

INSTANTIATE_TEST_SUITE_P(ValidEntityPositionTests, GridValidEntityPositionTestP,
                         Values(sf::Vector2f(-10.0f, 10.0f), sf::Vector2f(10.0f, -10.0f), sf::Vector2f(-10.0f, -10.0f),
                                sf::Vector2f(110.0f, 10.0f), sf::Vector2f(10.0f, 110.0f),
                                sf::Vector2f(110.0f, 110.0f)));

TEST_P(GridValidEntityPositionTestP, AddOutsideMapShouldLogError)
{
    const auto &position = GetParam();
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("is outside map")));
    grid_.Add(1, position, {2, 2});
    EXPECT_EQ(grid_.Count(), 0u);
}

class GridEntitiesInDifferentCellsTestP : public Grid100x1000x10Test,
                                          public WithParamInterface<std::pair<sf::Vector2f, sf::Vector2f>>
{
};

// Entities that are horizontal side-by-side, but are in different cells.
INSTANTIATE_TEST_SUITE_P(HorizontalCornerCaseTests, GridEntitiesInDifferentCellsTestP,
                         Values(std::make_pair(sf::Vector2f(17.0f, 10.0f), sf::Vector2f(20.0f, 10.0f)),
                                std::make_pair(sf::Vector2f(17.0f, 17.0f), sf::Vector2f(20.0f, 17.0f))));

// Entities that are vertical side-by-side, but are in different cells.
INSTANTIATE_TEST_SUITE_P(VerticalCornerCaseTests, GridEntitiesInDifferentCellsTestP,
                         Values(std::make_pair(sf::Vector2f(10.0f, 7.0f), sf::Vector2f(10.0f, 10.0f)),
                                std::make_pair(sf::Vector2f(17.0f, 7.0f), sf::Vector2f(17.0f, 10.0f))));

TEST_P(GridEntitiesInDifferentCellsTestP, EntitiesShouldBeDetectedInDifferentCells)
{
    const auto &pair = GetParam();
    grid_.Add(movableEntityId1_, pair.first, {2, 2});
    grid_.Add(movableEntityId2_, pair.second, {2, 2});
    std::unordered_set<EntityId> entitiesCell1, entitiesCell2;
    std::unordered_set<EntityId> staticEntitiesCell1, staticEntitiesCell2;
    EXPECT_CALL(collisionHandlerMock_, DetectCollisions)
        .Times(2)
        .WillOnce(DoAll(SaveArg<0>(&entitiesCell1), SaveArg<1>(&staticEntitiesCell1)))
        .WillOnce(DoAll(SaveArg<0>(&entitiesCell2), SaveArg<1>(&staticEntitiesCell2)));
    grid_.DetectCollisions();
    EXPECT_THAT(entitiesCell1, Contains(movableEntityId1_));
    EXPECT_THAT(staticEntitiesCell1, IsEmpty());
    EXPECT_THAT(entitiesCell2, Contains(movableEntityId2_));
    EXPECT_THAT(staticEntitiesCell2, IsEmpty());
}

}  // namespace Entity

}  // namespace FA
