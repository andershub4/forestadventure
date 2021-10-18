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
class BasicProperty;

class PropertyStore
{
public:
    template <class T>
    std::shared_ptr<T> AddProperty(EntityService *owner)
    {
        static_assert(std::is_base_of<BasicProperty, T>::value, "T must derive from BasicProperty");
        auto it = properties_.find(typeid(T));

        if (it != properties_.end()) {
            LOG_WARN(typeid(T).name(), " is already registered");
            return std::dynamic_pointer_cast<T>(properties_[typeid(T)]);
        }
        else {
            auto c = std::make_shared<T>(owner);
            properties_[typeid(T)] = c;
            return c;
        }
    }

    template <class T>
    std::shared_ptr<T> GetProperty() const
    {
        return std::dynamic_pointer_cast<T>(properties_.at(typeid(T)));
    }

    template <class T>
    bool HasProperty() const
    {
        auto it = properties_.find(typeid(T));
        return it != properties_.end();
    }

    void Awake();
    void Init();

private:
    std::unordered_map<std::type_index, std::shared_ptr<BasicProperty>> properties_;
};

}  // namespace Entity

}  // namespace FA
