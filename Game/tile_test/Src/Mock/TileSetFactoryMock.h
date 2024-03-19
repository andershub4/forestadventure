/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "TileSetFactoryIf.h"

namespace FA {

namespace Tile {

class TileSetFactoryMock : public TileSetFactoryIf
{
public:
    MOCK_METHOD(std::unique_ptr<TileSetIf>, Create,
                (const std::string& tsxDir, const std::vector<ParsedTile>& tiles, const ParsedTileSet& tileSet,
                 const std::string& imageSource),
                (const override));
};

class TileSetFactoryMockProxy : public TileSetFactoryIf
{
public:
    TileSetFactoryMockProxy(TileSetFactoryMock& mock)
        : mock_(mock)
    {}

    std::unique_ptr<TileSetIf> Create(const std::string& tsxDir, const std::vector<ParsedTile>& tiles,
                                      const ParsedTileSet& tileSet, const std::string& imageSource) const override
    {
        return mock_.Create(tsxDir, tiles, tileSet, imageSource);
    }

private:
    TileSetFactoryMock& mock_;
};

}  // namespace Tile

}  // namespace FA
