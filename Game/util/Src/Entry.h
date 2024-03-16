/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "LogLevel.h"

namespace LogLib {

class Entry
{
public:
    Entry(const LogLevel& logLevel, const std::string& fn, const std::string& str);

    std::string Str() const;

    friend bool operator==(const Entry& lhs, const Entry& rhs);

private:
    LogLevel logLevel_;
    std::string fn_{};
    std::string str_{};
};

bool operator==(const Entry& lhs, const Entry& rhs);

}  // namespace LogLib
