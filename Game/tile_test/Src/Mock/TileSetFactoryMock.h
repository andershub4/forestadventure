/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "BasicTileSetFactory.h"

namespace FA {

namespace Tile {

class TileSetFactoryMock : public BasicTileSetFactory
{
public:
    MOCK_METHOD(std::unique_ptr<BasicTileSet>, Create,
                (const std::string& tsxDir, const std::vector<ParsedTile>& tiles, const ParsedTileSet& tileSet,
                 const std::string& imageSource),
                (const override));
};

class TileSetFactoryMockProxy : public BasicTileSetFactory
{
public:
    TileSetFactoryMockProxy(TileSetFactoryMock& mock)
        : mock_(mock)
    {}

    std::unique_ptr<BasicTileSet> Create(const std::string& tsxDir, const std::vector<ParsedTile>& tiles,
                                         const ParsedTileSet& tileSet, const std::string& imageSource) const override
    {
        return mock_.Create(tsxDir, tiles, tileSet, imageSource);
    }

private:
    TileSetFactoryMock& mock_;
};

}  // namespace Tile

}  // namespace FA
