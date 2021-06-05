/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Platform {

struct Result
{
    Result() = default;

    Result(const std::string &errorMessage)
        : errorMessage_(errorMessage)
    {}

    bool IsOk() const { return errorMessage_.empty(); }

    std::string errorMessage_{};
};

}  // namespace Platform

}  // namespace FA
