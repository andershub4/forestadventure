/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Logging.h"

namespace FA {

namespace Shared {

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
            LOG_ERROR("Could not load %s", path.c_str());
        }
    }

    const R* Get(const K& key) const
    {
        auto it = resources_.find(key);

        if (it != resources_.end()) return it->second.get();

        std::ostringstream oss;
        oss << "Could not get " << key;
        LOG_ERROR("%s", oss.str().c_str());

        return nullptr;
    }

private:
    std::unordered_map<K, std::unique_ptr<R>> resources_;
};

}  // namespace Shared

}  // namespace FA
