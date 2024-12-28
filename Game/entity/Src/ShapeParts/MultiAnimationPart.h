/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "AnimationPartBase.h"
#include "MultiAnimationPartIf.h"

#include "Logging.h"

namespace FA {

namespace Entity {

template <class KeyT, class FrameT>
class MultiAnimationPart : public AnimationPartBase<MultiAnimationPartIf, FrameT, KeyT>
{
    using AnimationPartBase<MultiAnimationPartIf, FrameT, KeyT>::DrawableType;
    using SelectFn = std::function<std::shared_ptr<Shared::ImageAnimationIf<FrameT>>(
        const std::unordered_map<KeyT, std::shared_ptr<Shared::ImageAnimationIf<FrameT>>> &)>;

public:
    MultiAnimationPart(const KeyT *const key, DrawableType &drawable)
        : AnimationPartBase<MultiAnimationPartIf, FrameT, KeyT>(drawable)
    {
        selectFn_ = [key](const std::unordered_map<KeyT, std::shared_ptr<Shared::ImageAnimationIf<FrameT>>> &map) {
            bool found = map.find(*key) != map.end();
            std::shared_ptr<Shared::ImageAnimationIf<FrameT>> result{};

            if (found) {
                result = map.at(*key);
            }
            else {
                LOG_ERROR("%s can not be found", DUMP(key));
            }

            return result;
        };
    }

    virtual void Enter() override
    {
        this->animation_ = selectFn_(map_);
        this->animation_->Restart();
    }

    virtual void Register(const KeyT &key, std::shared_ptr<Shared::ImageAnimationIf<FrameT>> animation) override
    {
        auto it = map_.find(key);
        if (it != map_.end()) {
            LOG_WARN("%s is already registered", DUMP(key));
        }
        else {
            map_.insert({key, animation});
        }
    }

private:
    SelectFn selectFn_;
    std::unordered_map<KeyT, std::shared_ptr<Shared::ImageAnimationIf<FrameT>>> map_;
};

}  // namespace Entity

}  // namespace FA
