/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

std::string GetHead(const std::string& filePath);

std::string GetLocalAppDataPath();
std::string GetProgramDataPath();
std::string GetExePath();

}  // namespace FA
