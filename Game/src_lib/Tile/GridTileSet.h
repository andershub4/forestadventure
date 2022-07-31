/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "BasicTileSet.h"

namespace FA {

namespace Tile {

class GridTileSet : public BasicTileSet
{
public:
    struct Dimensions
    {
        unsigned int tileWidth_{};
        unsigned int tileHeight_{};
        unsigned int columns_{};
        unsigned int tileCount_{};
    };

    GridTileSet(const std::string &tsxDir, const std::string &textureFilePath, const Dimensions &dimensions);
    virtual ~GridTileSet();

    virtual void Create() override;
    virtual std::vector<Image> GetImages() const override;
    virtual std::unordered_map<int, FrameData> GetFrameDatas() const override;

private:
    std::string tsxDir_{};
    std::string textureFilePath_{};
    Dimensions dimensions_;
    std::string p_{};
    std::unordered_map<int, FrameData> frameData_;
};

}  // namespace Tile

}  // namespace FA
