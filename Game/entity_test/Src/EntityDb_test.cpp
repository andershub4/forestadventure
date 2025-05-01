/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "EntityDb.h"
#include "EntityMock.h"
#include "Mock/LoggerMock.h"

using namespace testing;

namespace FA {

namespace Entity {

class EntityDbTest : public Test
{
protected:
    EntityDbTest()
        : entityMockProxy1_{std::make_unique<EntityMockProxy>(entityMock1_)}
        , entityMockProxy2_{std::make_unique<EntityMockProxy>(entityMock2_)}
    {}

    StrictMock<EntityMock> entityMock1_;
    StrictMock<EntityMock> entityMock2_;
    StrictMock<Shared::LoggerMock> loggerMock_;
    // Declare EntityDb db_ after entityMocks, the order on stack is important,
    // otherwise EntityDb destructor will execute using destroyed entityMocks
    EntityDb db_;
    std::unique_ptr<EntityMockProxy> entityMockProxy1_;
    std::unique_ptr<EntityMockProxy> entityMockProxy2_;
};

TEST_F(EntityDbTest, AddEntityShouldSucceed)
{
    EXPECT_CALL(entityMock1_, GetId()).WillOnce(Return(1));
    EXPECT_CALL(entityMock1_, Destroy());
    db_.AddEntity(std::move(entityMockProxy1_));
}

TEST_F(EntityDbTest, AddDuplicatedEntityShouldLogError)
{
    EntityId id{1};
    EXPECT_CALL(entityMock1_, GetId()).WillOnce(Return(id));
    EXPECT_CALL(entityMock1_, Destroy());
    db_.AddEntity(std::move(entityMockProxy1_));
    EXPECT_CALL(entityMock2_, GetId()).WillOnce(Return(id));
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry("{id: 1} already exist"));
    db_.AddEntity(std::move(entityMockProxy2_));
}

TEST_F(EntityDbTest, GetEntityShouldReturnEntity)
{
    EntityId id{1};
    EXPECT_CALL(entityMock1_, GetId()).WillRepeatedly(Return(id));
    EXPECT_CALL(entityMock1_, Destroy());
    db_.AddEntity(std::move(entityMockProxy1_));
    auto& result = db_.GetEntity(id);
    EXPECT_EQ(result.GetId(), id);
}

TEST_F(EntityDbTest, GetEntityShouldThrowWhenIdDoesNotExist)
{
    EntityId id{1};
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry("{id: 1} does not exist"));
    EXPECT_THROW(db_.GetEntity(id), std::out_of_range);
}

TEST_F(EntityDbTest, DeleteEntityShouldSucceed)
{
    EntityId id{1};
    EXPECT_CALL(entityMock1_, GetId()).WillOnce(Return(id));
    db_.AddEntity(std::move(entityMockProxy1_));
    EXPECT_CALL(entityMock1_, Destroy());
    db_.DeleteEntity(id);
}

TEST_F(EntityDbTest, DeleteEntityShouldThrowWhenIdDoesNotExist)
{
    EntityId id{1};
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry("{id: 1} does not exist"));
    EXPECT_THROW(db_.DeleteEntity(id), std::out_of_range);
}

}  // namespace Entity

}  // namespace FA
