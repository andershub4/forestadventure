/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Logging.h"

namespace FA {

namespace Entity {

class EntityService;
class BasicAttribute;

class AttributeStore
{
public:
    template <class T>
    std::shared_ptr<T> AddAttribute(EntityService *owner)
    {
        static_assert(std::is_base_of<BasicAttribute, T>::value, "T must derive from BasicAttribute");
        auto it = attributes_.find(typeid(T));

        if (it != attributes_.end()) {
            LOG_WARN(typeid(T).name(), " is already registered");
            return std::dynamic_pointer_cast<T>(attributes_[typeid(T)]);
        }
        else {
            auto c = std::make_shared<T>(owner);
            attributes_[typeid(T)] = c;
            return c;
        }
    }

    template <class T>
    std::shared_ptr<T> GetAttribute() const
    {
        return std::dynamic_pointer_cast<T>(attributes_.at(typeid(T)));
    }

    template <class T>
    bool HasAttribute() const
    {
        auto it = attributes_.find(typeid(T));
        return it != attributes_.end();
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<BasicAttribute>> attributes_;
};

}  // namespace Entity

}  // namespace FA
