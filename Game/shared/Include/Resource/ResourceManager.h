/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Logging.h"
#include "ResourceId.h"

namespace FA {

namespace Shared {

template <class R>
class ResourceManager
{
public:
    ResourceManager(std::function<std::unique_ptr<R>()> createFn)
        : createFn_(createFn)
    {}

    ResourceId Load(const std::string& path)
    {
        auto it = paths_.find(path);
        if (it != paths_.end()) {
            LOG_WARN("%s is already loaded", DUMP(path));
            return paths_.at(path);
        }

        auto resource = createFn_();

        if (resource->loadFromFile(path)) {
            paths_[path] = id_;
            resources_.emplace(id_, std::move(resource));
            auto n = resources_.size();
            LOG_INFO("Loaded %u resource(s)", n);
            return id_++;
        }
        else {
            LOG_ERROR("Could not load %s", DUMP(path));
            return InvalidResourceId;
        }
    }

    const R* Get(ResourceId id) const
    {
        auto it = resources_.find(id);

        if (it != resources_.end()) return it->second.get();

        LOG_ERROR("Could not get %s", DUMP(id));

        return nullptr;
    }

private:
    ResourceId id_{0};
    std::unordered_map<ResourceId, std::unique_ptr<R>> resources_;
    std::function<std::unique_ptr<R>()> createFn_;
    std::unordered_map<std::string, ResourceId> paths_;
};

}  // namespace Shared

}  // namespace FA
