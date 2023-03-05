/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tinyxml2/tinyxml2.h>
#include "ParseHelper.h"

#include "TmxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TmxParserInt : public Test
{
protected:
    using ParseResult = ParseResult<tinyxml2::XMLError>;

    TmxParserInt()
        : helper_(std::make_shared<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>>())
        , parser_(helper_)
    {}

    const std::string xmlBuffer_ = "xml content";
    tinyxml2::XMLDocument doc_;
    std::shared_ptr<ParseHelper<tinyxml2::XMLElement, tinyxml2::XMLError>> helper_;
    TmxParser<tinyxml2::XMLDocument, tinyxml2::XMLElement, tinyxml2::XMLError> parser_;
};

TEST_F(TmxParserInt, ParseValidMapShouldSucceed)
{
    ParsedTmx parsedTmx;
    parser_.Parse(doc_, xmlBuffer_, parsedTmx);

    EXPECT_TRUE(parsedTmx.layers_.empty());
}

}  // namespace Tile

}  // namespace FA
