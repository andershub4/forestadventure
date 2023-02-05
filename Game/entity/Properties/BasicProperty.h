/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Entity {

struct BasicProperty
{
    BasicProperty(const std::string name)
        : name_(name)
    {}
    std::string name_;

    virtual ~BasicProperty() = default;
};

}  // namespace Entity

}  // namespace FA
