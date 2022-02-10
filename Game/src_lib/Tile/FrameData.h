/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Resource/Frame.h"

namespace FA {

namespace Tile {

struct FrameData
{
    Frame frame_;
    std::vector<Frame> frames_;
};

}  // namespace Tile

}  // namespace FA
