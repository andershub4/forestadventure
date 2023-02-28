/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Logging.h"

namespace FA {

namespace Entity {

template <class KeyT, class ItemT>
class ResourceTable
{
public:
    ResourceTable(std::function<KeyT()> keyFn)
        : keyFn_(keyFn)
    {}

    ~ResourceTable() = default;

    void RegisterResource(const KeyT& key, const ItemT& item)
    {
        auto k = KeyToStr(key);
        map_[k] = item;
    }

    ItemT GetResource() const
    {
        auto k = KeyToStr(keyFn_());
        if (map_.find(k) != map_.end()) {
            return map_.at(k);
        }

        LOG_ERROR("Could not find key: %s", k.c_str());
        return ItemT{};
    }

private:
    std::unordered_map<std::string, ItemT> map_;
    std::function<KeyT()> keyFn_;

private:
    std::string KeyToStr(const KeyT& item) const
    {
        std::stringstream ss;
        ss << item;
        return ss.str();
    }
};

}  // namespace Entity

}  // namespace FA
