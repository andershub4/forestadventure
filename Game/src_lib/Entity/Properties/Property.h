/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicProperty.h"

namespace FA {

namespace Entity {

template <class T>
struct Property : public BasicProperty
{
    Property(const std::string& name, const T& value)
        : BasicProperty(name)
        , value_(value)
    {}

    T value_;
};

}  // namespace Entity

}  // namespace FA
