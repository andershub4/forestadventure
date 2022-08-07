/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TsxParser.h"

enum XMLError {
    XML_SUCCESS = 0,
    XML_NO_ATTRIBUTE,
    XML_WRONG_ATTRIBUTE_TYPE,
    XML_ERROR_FILE_NOT_FOUND,
    XML_ERROR_FILE_COULD_NOT_BE_OPENED,
    XML_ERROR_FILE_READ_ERROR,
    XML_ERROR_PARSING_ELEMENT,
    XML_ERROR_PARSING_ATTRIBUTE,
    XML_ERROR_PARSING_TEXT,
    XML_ERROR_PARSING_CDATA,
    XML_ERROR_PARSING_COMMENT,
    XML_ERROR_PARSING_DECLARATION,
    XML_ERROR_PARSING_UNKNOWN,
    XML_ERROR_EMPTY_DOCUMENT,
    XML_ERROR_MISMATCHED_ELEMENT,
    XML_ERROR_PARSING,
    XML_CAN_NOT_CONVERT_TEXT,
    XML_NO_TEXT_NODE,
    XML_ELEMENT_DEPTH_EXCEEDED,

    XML_ERROR_COUNT
};

class XMLElementMock
{
public:
    MOCK_METHOD(const char*, Attribute, (const char* name), (const));
    MOCK_METHOD(XMLElementMock*, FirstChildElement, (const char* name));
    MOCK_METHOD(const XMLElementMock*, FirstChildElement, (const char* name), (const));
    MOCK_METHOD(XMLElementMock*, NextSiblingElement, (const char* name));
    MOCK_METHOD(const XMLElementMock*, NextSiblingElement, (const char* name), (const));
    MOCK_METHOD(XMLError, QueryAttribute, (const char* name, int* value), (const));
    MOCK_METHOD(XMLError, QueryAttribute, (const char* name, unsigned int* value), (const));
};

class XMLDocumentMock
{
public:
    MOCK_METHOD(XMLError, LoadFile, (const char* filename));
    MOCK_METHOD(bool, Error, (), (const));
    MOCK_METHOD(const XMLElementMock*, FirstChildElement, (const char* name), (const));
    MOCK_METHOD(XMLElementMock*, FirstChildElement, (const char* name));
};

using ::testing::_;
using ::testing::An;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrEq;

TEST(TestTsxParser, ParseShouldFailDueToError)
{
    XMLDocumentMock docMock;
    FA::Tile::TsxParser<XMLDocumentMock, XMLElementMock> p;

    EXPECT_CALL(docMock, LoadFile(_));
    EXPECT_CALL(docMock, Error()).WillOnce(Return(true));

    EXPECT_EQ(false, (p.Parse("t", &docMock)));
}

TEST(TestTsxParser, ParseShouldSucceed)
{
    XMLDocumentMock docMock;
    XMLElementMock tileSetElementMock;
    FA::Tile::TsxParser<XMLDocumentMock, XMLElementMock> p;

    EXPECT_CALL(docMock, LoadFile(_));
    EXPECT_CALL(docMock, Error()).WillOnce(Return(false));
    EXPECT_CALL(docMock, FirstChildElement(StrEq("tileset"))).WillOnce(Return(&tileSetElementMock));

    EXPECT_CALL(tileSetElementMock, Attribute(StrEq("name"))).WillOnce(Return("a"));
    EXPECT_CALL(tileSetElementMock, QueryAttribute(_, An<int*>()))
        .Times(4)
        .WillRepeatedly(DoAll(SetArgPointee<1>(3), Return(XML_SUCCESS)));

    XMLElementMock tileElementMock;
    EXPECT_CALL(tileSetElementMock, FirstChildElement(_)).WillOnce(Return(&tileElementMock));
    EXPECT_CALL(tileElementMock, QueryAttribute(StrEq("id"), An<int*>()))
        .WillOnce(DoAll(SetArgPointee<1>(10), Return(XML_SUCCESS)));
    XMLElementMock imageElementMock;
    EXPECT_CALL(tileElementMock, FirstChildElement(StrEq("image"))).WillOnce(Return(&imageElementMock));

    // ParseImageElement
    EXPECT_CALL(imageElementMock, Attribute(StrEq("source"))).WillOnce(Return("source_name"));
    EXPECT_CALL(imageElementMock, QueryAttribute(_, An<unsigned int*>()))
        .Times(2)
        .WillRepeatedly(DoAll(SetArgPointee<1>(15), Return(XML_SUCCESS)));

    EXPECT_CALL(tileElementMock, FirstChildElement(StrEq("animation"))).WillOnce(Return(nullptr));

    EXPECT_CALL(tileElementMock, NextSiblingElement(_)).WillOnce(Return(nullptr));

    EXPECT_EQ(true, (p.Parse("t", &docMock)));
}
