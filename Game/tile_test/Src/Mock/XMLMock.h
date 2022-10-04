/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

namespace FA {

namespace Tile {

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
    MOCK_METHOD(XMLError, QueryStringAttribute, (const char* name, const char** value), (const));
    MOCK_METHOD(XMLError, QueryAttribute, (const char* name, int* value), (const));
    MOCK_METHOD(XMLError, QueryAttribute, (const char* name, unsigned int* value), (const));
    MOCK_METHOD(const char*, GetText, (), (const));
};

class XMLDocumentMock
{
public:
    MOCK_METHOD(XMLError, LoadFile, (const char* filename));
    MOCK_METHOD(XMLError, Parse, (const char* xml));
    MOCK_METHOD(bool, Error, (), (const));
    MOCK_METHOD(const XMLElementMock*, FirstChildElement, (const char* name), (const));
    MOCK_METHOD(XMLElementMock*, FirstChildElement, (const char* name));
};

}  // namespace Tile

}  // namespace FA
