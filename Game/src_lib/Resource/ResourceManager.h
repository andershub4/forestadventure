/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Logging.h"

namespace FA {

template <class K, class R>
class ResourceManager
{
public:
    void Add(const K& key, const std::string& path)
    {
        auto resource = std::make_unique<R>();

        if (resource->loadFromFile(path)) {
            resources_.emplace(key, std::move(resource));
        }
        else {
            LOG_ERROR("Could not load ", path);
        }
    }

    const R* Get(const K& key) const
    {
        auto it = resources_.find(key);

        if (it != resources_.end()) return it->second.get();

        LOG_ERROR("Could not get ", key);

        return nullptr;
    }

private:
    std::unordered_map<K, std::unique_ptr<R>> resources_;
};

}  // namespace FA
