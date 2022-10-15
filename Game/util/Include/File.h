/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

std::string GetBuffer(std::istream& ifd);
std::string GetFileBuffer(const std::string& fileName);

}  // namespace FA
