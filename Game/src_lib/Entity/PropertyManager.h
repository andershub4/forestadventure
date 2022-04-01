/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Logging.h"
#include "PropertyStore.h"

namespace FA {

namespace Entity {

class PropertyManager
{
public:
    PropertyManager();

    void ReadCustomProperty(const std::string &name, const std::string &valueStr);

    template <class T>
    void Register(const std::string &name, const T &value)
    {
        propertyStore_.Add<T>(name, value);
    }

    template <class T>
    T Get(const std::string &name) const
    {
        return propertyStore_.Get<T>(name);
    }

    template <class T>
    void Set(const std::string &name, const T &value)
    {
        propertyStore_.Set<T>(name, value);
    }

private:
    PropertyStore propertyStore_;
};

}  // namespace Entity

}  // namespace FA
