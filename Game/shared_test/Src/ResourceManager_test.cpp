/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <string>

#include <SFML/Graphics/Rect.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LoggerMock.h"
#include "Resource/ResourceManager.h"
#include "TextureMock.h"

using namespace testing;

namespace FA {

namespace Shared {

class ResourceManagerTest : public Test
{
protected:
    using SomeResourceMock = Graphic::TextureMock;

    ResourceManagerTest()
        : resourceManager_(createFn_.AsStdFunction())
    {}

    virtual void SetUp() override { resourceMock_ = std::make_unique<SomeResourceMock>(); }

    const std::string path_ = "C:/MyFolder/MyFile.jpg";
    StrictMock<LoggerMock> loggerMock_;
    std::unique_ptr<SomeResourceMock> resourceMock_;
    MockFunction<std::unique_ptr<SomeResourceMock>()> createFn_;
    ResourceManager<SomeResourceMock> resourceManager_;
};

TEST_F(ResourceManagerTest, LoadResourceShouldSucceed)
{
    auto expectedPtr = resourceMock_.get();
    EXPECT_CALL(*resourceMock_, loadFromFile(path_)).WillOnce(Return(true));
    EXPECT_CALL(createFn_, Call).WillOnce(Return(ByMove(std::move(resourceMock_))));
    EXPECT_CALL(loggerMock_, MakeInfoLogEntry("Loaded 1 resource(s)"));

    auto id = resourceManager_.Load(path_);
    EXPECT_EQ(id, 0);
    auto result = resourceManager_.Get(id);
    EXPECT_EQ(result, expectedPtr);
}

TEST_F(ResourceManagerTest, LoadDuplicatedResourceShouldWarn)
{
    EXPECT_CALL(*resourceMock_, loadFromFile(path_)).WillOnce(Return(true));
    EXPECT_CALL(createFn_, Call).WillOnce(Return(ByMove(std::move(resourceMock_))));
    EXPECT_CALL(loggerMock_, MakeInfoLogEntry("Loaded 1 resource(s)"));

    ResourceId expectedId = 0;
    auto id1 = resourceManager_.Load(path_);
    EXPECT_EQ(id1, expectedId);

    EXPECT_CALL(loggerMock_, MakeWarnLogEntry(ContainsRegex("C:/MyFolder/MyFile.jpg.*is already loaded")));
    auto id2 = resourceManager_.Load(path_);
    EXPECT_EQ(id2, expectedId);
}

TEST_F(ResourceManagerTest, LoadResourceShouldFail)
{
    EXPECT_CALL(*resourceMock_, loadFromFile(path_)).WillOnce(Return(false));
    EXPECT_CALL(createFn_, Call).WillOnce(Return(ByMove(std::move(resourceMock_))));
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("Could not load.*C:/MyFolder/MyFile.jpg")));

    auto id = resourceManager_.Load(path_);
    EXPECT_EQ(id, InvalidResourceId);
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("Could not get.*0")));
    auto result = resourceManager_.Get(0);
    EXPECT_THAT(result, IsNull());
}

TEST_F(ResourceManagerTest, GetResourceShouldReturnNull)
{
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(ContainsRegex("Could not get.*123")));
    auto result = resourceManager_.Get(123);
    EXPECT_THAT(result, IsNull());
}

}  // namespace Shared

}  // namespace FA
