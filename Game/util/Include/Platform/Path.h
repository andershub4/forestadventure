/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "Result.h"

namespace FA {

namespace Util {

Result GetShortPathNameW(const std::wstring& longPath, std::wstring& shortPath);
Result GetShortPathNameA(const std::wstring& longPath, std::string& shortPath);
std::string GetExeFileName();

}  // namespace Util

}  // namespace FA
