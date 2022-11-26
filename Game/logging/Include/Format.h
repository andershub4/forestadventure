/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <cstdarg>
#include <string>

namespace LogLib {

class Format
{
public:
    static std::string ToString(const char* format, ...);

private:
    static constexpr int maxLogEntrySize_{40000};  // arbitrary number
};

}  // namespace LogLib
