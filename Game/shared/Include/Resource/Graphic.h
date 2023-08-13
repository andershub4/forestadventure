/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "ImageData.h"

namespace FA {

namespace Shared {

struct Graphic
{
    using Animation = std::vector<ImageData>;
    Animation animation_;
    ImageData image_;
};

}  // namespace Shared

}  // namespace FA
