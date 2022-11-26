/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Format.h"

namespace LogLib {

std::string Format::ToString(const char* format, ...)
{
    std::string result;

    if (format != nullptr) {
        va_list args;
        va_start(args, format);
        char buffer[maxLogEntrySize_];
        memset(buffer, 0, maxLogEntrySize_ * sizeof(char));
        vsnprintf(buffer, maxLogEntrySize_ - 1, format, args);
        result = std::string(buffer);
        va_end(args);
    }

    return result;
}

}  // namespace LogLib
