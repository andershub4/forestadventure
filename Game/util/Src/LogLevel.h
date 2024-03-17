/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

namespace FA {

namespace Util {

enum class LogLevel { Debug, Info, Warn, Error };

inline std::ostream& operator<<(std::ostream& os, const LogLevel& e)
{
    std::string str;
    switch (e) {
        case LogLevel::Debug:
            str = "DEBUG";
            break;
        case LogLevel::Info:
            str = "INFO";
            break;
        case LogLevel::Warn:
            str = "WARNING";
            break;
        case LogLevel::Error:
            str = "ERROR";
            break;
    }

    os << str;

    return os;
}

}  // namespace Util

}  // namespace FA
