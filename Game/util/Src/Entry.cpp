/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Entry.h"

#include <sstream>
#include <tuple>

namespace FA {

namespace Util {

Entry::Entry(const LogLevel& logLevel, const std::string& fn, const std::string& str)
    : logLevel_(logLevel)
    , fn_(fn)
    , str_(str)
{}

std::string Entry::Str() const
{
    std::stringstream ss;
    ss << "[" << logLevel_ << " | " << fn_ << "]: " << str_;

    return ss.str();
}

bool operator==(const Entry& lhs, const Entry& rhs)
{
    return (std::tie(lhs.logLevel_, lhs.fn_, lhs.str_) == std::tie(rhs.logLevel_, rhs.fn_, rhs.str_));
}

}  // namespace Util

}  // namespace FA
