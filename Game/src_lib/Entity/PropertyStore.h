/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Logging.h"
#include "Properties/Property.h"

namespace FA {

namespace Entity {

class PropertyStore
{
public:
    template <class T>
    void Add(const std::string& name, const T& value)
    {
        properties_[name] = std::make_shared<Property<T>>(name, value);
    }

    template <class T>
    T Get(const std::string& name) const
    {
        auto a = properties_.at(name);
        auto p = std::dynamic_pointer_cast<Property<T>>(a);
        return p->value_;
    }

    template <class T>
    void Set(const std::string& name, const T& value)
    {
        auto a = properties_.at(name);
        auto p = std::dynamic_pointer_cast<Property<T>>(a);
        p->value_ = value;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<BasicProperty>> properties_;
};

}  // namespace Entity

}  // namespace FA
