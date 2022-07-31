#pragma once
/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Image.h"
#include "ParsedFrame.h"

namespace FA {

namespace Tile {

struct Tile
{
    int id_{};
    Image image_;
    std::vector<ParsedFrame> frames_;
};

}  // namespace Tile

}  // namespace FA
