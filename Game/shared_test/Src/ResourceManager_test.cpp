/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <string>

#include <SFML/Graphics/Rect.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Mock/LogMock.h"
#include "Resource/ResourceManager.h"

using namespace testing;

namespace FA {

namespace Shared {

class SomeResourceMock
{
public:
    MOCK_METHOD(bool, loadFromFileImpl, (const std::string& fileName, const sf::IntRect& area));
    bool loadFromFile(const std::string& fileName, const sf::IntRect& area = sf::IntRect())
    {
        return loadFromFileImpl(fileName, area);
    }
};

class ResourceManagerTest : public Test
{
protected:
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

TEST_F(ResourceManagerTest, AddResourceShouldSucceed)
{
    auto expectedPtr = resourceMock_.get();
    EXPECT_CALL(*resourceMock_, loadFromFileImpl).WillOnce(Return(true));
    EXPECT_CALL(createFn_, Call).WillOnce(Return(ByMove(std::move(resourceMock_))));

    auto id = resourceManager_.Load(path_);
    auto result = resourceManager_.Get(id);
    EXPECT_EQ(id, 0);
    EXPECT_EQ(result, expectedPtr);
}

TEST_F(ResourceManagerTest, AddResourceShouldFail)
{
    EXPECT_CALL(*resourceMock_, loadFromFileImpl).WillOnce(Return(false));
    EXPECT_CALL(createFn_, Call).WillOnce(Return(ByMove(std::move(resourceMock_))));
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("Could not load C:/MyFolder/MyFile.jpg")));

    auto id = resourceManager_.Load(path_);
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("Could not get 0")));
    auto result = resourceManager_.Get(0);
    EXPECT_THAT(id, InvalidTextureId);
    EXPECT_THAT(result, IsNull());
}

TEST_F(ResourceManagerTest, GetResourceShouldReturnNull)
{
    EXPECT_CALL(loggerMock_, MakeErrorLogEntry(StrEq("Could not get 123")));
    auto result = resourceManager_.Get(123);
    EXPECT_THAT(result, IsNull());
}

}  // namespace Shared

}  // namespace FA
