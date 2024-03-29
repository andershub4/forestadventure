/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Format.h"

namespace FA {

namespace Util {

static constexpr int maxLogEntrySize{40000};  // arbitrary number

std::string ToString(const char* format, ...)
{
    std::string result;

    if (format != nullptr) {
        va_list args;
        va_start(args, format);
        char buffer[maxLogEntrySize + 1];
        memset(buffer, 0, maxLogEntrySize * sizeof(char));
        vsnprintf(buffer, sizeof(buffer), format, args);
        result = std::string(buffer);
        va_end(args);
    }

    return result;
}

}  // namespace Util

}  // namespace FA
