/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Frame.h"

namespace FA {

namespace Shared {

struct Graphic
{
    using Animation = std::vector<Frame>;
    Animation animation_;
    Frame image_;
};

}  // namespace Shared

}  // namespace FA
