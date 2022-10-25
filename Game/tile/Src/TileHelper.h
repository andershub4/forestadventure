/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Tile {

std::string GetFilePath(const std::string& baseDir, const std::string& source);

}  // namespace Tile

}  // namespace FA
