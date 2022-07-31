/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Tile {

struct Image
{
    std::string path_;
    int width_{};
    int height_{};
};

}  // namespace Tile

}  // namespace FA
