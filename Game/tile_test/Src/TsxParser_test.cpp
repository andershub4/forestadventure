/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <vector>

#include <gtest/gtest.h>

#include "Mock/XMLMock.h"

#include "TsxParser.h"

using namespace testing;

namespace FA {

namespace Tile {

class TestTsxParser : public Test
{
protected:
    struct TileSetData
    {
        std::string name_{};
        unsigned int tileWidth_{};
        unsigned int tileHeight_{};
        unsigned int tileCount_{};
        unsigned int columns_{};
        struct Grid
        {
            std::string orientation_{};
            unsigned int width_{};
            unsigned int height_{};
        };
        Grid grid_{};
        struct Image
        {
            bool valid_{false};
            std::string source_{};
            unsigned int width_{};
            unsigned int height_{};
        };
        Image image_{};

        struct Tile
        {
            unsigned int id_{};
            struct Animation
            {
                bool valid_{false};
                struct Frame
                {
                    unsigned int tileId_{};
                    unsigned int duration_{};
                };
                std::vector<Frame> frames_;
            };
            Image image_;          // at most 1 image
            Animation animation_;  // at most 1 animation
        };
        std::vector<Tile> tiles_;  // any number of tiles;
    };

    static TileSetData GetValidImageData1();
    static TileSetData GetValidGridData1();

    void VerifyTileElements(const std::vector<TileSetData::Tile>& tiles);
    void VerifyImageElement(const TileSetData::Image& image);

    XMLDocumentMock docMock_;
    XMLElementMock tileSetElementMock_;
    std::vector<std::shared_ptr<XMLElementMock>> tileElementMocks_;
    std::vector<std::shared_ptr<XMLElementMock>> imageElementMocks_;
    std::vector<std::shared_ptr<XMLElementMock>> animationElementMocks_;
    std::vector<std::shared_ptr<XMLElementMock>> frameElementMocks_;
};

TestTsxParser::TileSetData TestTsxParser::GetValidImageData1()
{
    return {"tileset",
            32u,
            80u,
            3u,
            0u,
            {},
            {},
            {{0u, {true, "source1.png", 32u, 80u}, {true, {{0u, 100u}, {1u, 100u}, {2u, 100u}}}},
             {1u, {true, "source2.png", 32u, 80u}, {}},
             {2u, {true, "source3.png", 32u, 80u}, {}}}};
}

TestTsxParser::TileSetData TestTsxParser::GetValidGridData1()
{
    return {"tileset", 16u, 16u, 1088u, 34u, {}, {true, "image source", 544u, 512u}, {}};
}

void TestTsxParser::VerifyTileElements(const std::vector<TileSetData::Tile>& tiles)
{
    if (tiles.empty()) {
        EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("tile"))).WillOnce(Return(nullptr));
        return;
    }

    bool first = true;
    auto m = std::make_shared<XMLElementMock>();

    for (const auto& tile : tiles) {
        if (first) {
            EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("tile"))).WillOnce(Return(m.get()));
            first = false;
        }
        else {
            auto current = m;
            m = std::make_shared<XMLElementMock>();
            EXPECT_CALL(*current, NextSiblingElement(StrEq("tile"))).WillOnce(Return(m.get()));
        }
        tileElementMocks_.push_back(m);

        EXPECT_CALL(*m, QueryAttribute(StrEq("id"), An<int*>()))
            .WillOnce(DoAll(SetArgPointee<1>(tile.id_), Return(XML_SUCCESS)));

        if (tile.image_.valid_) {
            auto imageElementMock = std::make_shared<XMLElementMock>();
            EXPECT_CALL(*m, FirstChildElement(StrEq("image"))).WillOnce(Return(imageElementMock.get()));
            imageElementMocks_.push_back(imageElementMock);

            // ParseImageElement
            EXPECT_CALL(*imageElementMock, Attribute(StrEq("source"))).WillOnce(Return(tile.image_.source_.c_str()));
            EXPECT_CALL(*imageElementMock, QueryAttribute(StrEq("width"), An<unsigned int*>()))
                .WillOnce(DoAll(SetArgPointee<1>(tile.image_.width_), Return(XML_SUCCESS)));
            EXPECT_CALL(*imageElementMock, QueryAttribute(StrEq("height"), An<unsigned int*>()))
                .WillOnce(DoAll(SetArgPointee<1>(tile.image_.height_), Return(XML_SUCCESS)));
        }
        else {
            EXPECT_CALL(*m, FirstChildElement(StrEq("image"))).WillOnce(Return(nullptr));
        }

        if (tile.animation_.valid_) {
            auto animationElementMock = std::make_shared<XMLElementMock>();
            EXPECT_CALL(*m, FirstChildElement(StrEq("animation"))).WillOnce(Return(animationElementMock.get()));
            animationElementMocks_.push_back(animationElementMock);

            auto f = std::make_shared<XMLElementMock>();
            bool first = true;
            for (const auto& frame : tile.animation_.frames_) {
                if (first) {
                    EXPECT_CALL(*animationElementMock, FirstChildElement(StrEq("frame"))).WillOnce(Return(f.get()));
                    first = false;
                }
                else {
                    auto current = f;
                    f = std::make_shared<XMLElementMock>();
                    EXPECT_CALL(*current, NextSiblingElement(StrEq("frame"))).WillOnce(Return(f.get()));
                }
                frameElementMocks_.push_back(f);

                // ParseFrameElement
                EXPECT_CALL(*f, QueryAttribute(StrEq("tileid"), An<int*>()))
                    .WillOnce(DoAll(SetArgPointee<1>(frame.tileId_), Return(XML_SUCCESS)));
                EXPECT_CALL(*f, QueryAttribute(StrEq("duration"), An<int*>()))
                    .WillOnce(DoAll(SetArgPointee<1>(frame.duration_), Return(XML_SUCCESS)));
            }
            EXPECT_CALL(*f, NextSiblingElement(StrEq("frame"))).WillOnce(Return(nullptr));
        }
        else {
            EXPECT_CALL(*m, FirstChildElement(StrEq("animation"))).WillOnce(Return(nullptr));
        }
    }

    EXPECT_CALL(*m, NextSiblingElement(StrEq("tile"))).WillOnce(Return(nullptr));
}

void TestTsxParser::VerifyImageElement(const TileSetData::Image& image)
{
    if (image.valid_) {
        auto imageElementMock = std::make_shared<XMLElementMock>();
        EXPECT_CALL(tileSetElementMock_, FirstChildElement(StrEq("image"))).WillOnce(Return(imageElementMock.get()));
        imageElementMocks_.push_back(imageElementMock);

        // ParseImageElement
        EXPECT_CALL(*imageElementMock, Attribute(StrEq("source"))).WillOnce(Return(image.source_.c_str()));
        EXPECT_CALL(*imageElementMock, QueryAttribute(StrEq("width"), An<unsigned int*>()))
            .WillOnce(DoAll(SetArgPointee<1>(image.width_), Return(XML_SUCCESS)));
        EXPECT_CALL(*imageElementMock, QueryAttribute(StrEq("height"), An<unsigned int*>()))
            .WillOnce(DoAll(SetArgPointee<1>(image.height_), Return(XML_SUCCESS)));
    }
}

TEST_F(TestTsxParser, ParseShouldFailDueToError)
{
    FA::Tile::TsxParser<XMLDocumentMock, XMLElementMock> p;

    EXPECT_CALL(docMock_, LoadFile(StrEq("test.txt")));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(true));

    EXPECT_EQ(false, (p.Parse("test.txt", &docMock_)));
}

TEST_F(TestTsxParser, ParseValidImageDataShouldSucceed)
{
    FA::Tile::TsxParser<XMLDocumentMock, XMLElementMock> p;
    std::string fileName = "test.txt";
    EXPECT_CALL(docMock_, LoadFile(StrEq(fileName)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock_));

    auto data = TestTsxParser::GetValidImageData1();

    EXPECT_CALL(tileSetElementMock_, Attribute(StrEq("name"))).WillOnce(Return(data.name_.c_str()));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("tilewidth"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("tileheight"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("tilecount"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("columns"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.columns_), Return(XML_SUCCESS)));

    VerifyTileElements(data.tiles_);
    VerifyImageElement(data.image_);

    EXPECT_EQ(true, (p.Parse(fileName, &docMock_)));
}

TEST_F(TestTsxParser, ParseValidGridDataShouldSucceed)
{
    FA::Tile::TsxParser<XMLDocumentMock, XMLElementMock> p;
    std::string fileName = "test.txt";
    EXPECT_CALL(docMock_, LoadFile(StrEq(fileName)));
    EXPECT_CALL(docMock_, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock_, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock_));

    auto data = TestTsxParser::GetValidGridData1();

    EXPECT_CALL(tileSetElementMock_, Attribute(StrEq("name"))).WillOnce(Return(data.name_.c_str()));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("tilewidth"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.tileWidth_), Return(XML_SUCCESS)));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("tileheight"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.tileHeight_), Return(XML_SUCCESS)));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("tilecount"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.tileCount_), Return(XML_SUCCESS)));
    EXPECT_CALL(tileSetElementMock_, QueryAttribute(StrEq("columns"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(data.columns_), Return(XML_SUCCESS)));

    VerifyTileElements(data.tiles_);
    VerifyImageElement(data.image_);

    EXPECT_EQ(true, (p.Parse(fileName, &docMock_)));
}

}  // namespace Tile

}  // namespace FA
