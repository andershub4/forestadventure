/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Util {

std::string GetHead(const std::string& filePath);

std::string GetLogPath();
std::string GetAssetsPath();

}  // namespace Util

}  // namespace FA
