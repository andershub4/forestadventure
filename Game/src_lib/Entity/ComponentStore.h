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

class BasicComponent;

class ComponentStore
{
public:
    template <class T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<BasicComponent, T>::value, "T must derive from BasicComponent");
        auto it = components_.find(typeid(T));

        if (it != components_.end()) {
            LOG_WARN(typeid(T).name(), " is already registered");
            return std::dynamic_pointer_cast<T>(components_[typeid(T)]);
        }
        else {
            auto c = std::make_shared<T>(std::forward<Args>(args)...);
            components_[typeid(T)] = c;
            return c;
        }
    }

    template <class T>
    std::shared_ptr<T> GetComponent() const
    {
        return std::dynamic_pointer_cast<T>(components_.at(typeid(T)));
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<BasicComponent>> components_;
};

}  // namespace Entity

}  // namespace FA
