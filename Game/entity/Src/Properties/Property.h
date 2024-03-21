/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "PropertyIf.h"

namespace FA {

namespace Entity {

template <class T>
struct Property : public PropertyIf
{
    Property(const std::string& name, const T& value)
        : value_(value)
        , name_(name)
    {}

    T value_;
    std::string name_;
};

}  // namespace Entity

}  // namespace FA
