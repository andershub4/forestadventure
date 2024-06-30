/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "Animation/ImageAnimation.h"
#include "BasicShapePart.h"
#include "Logging.h"
#include "Sequence.h"
#include "Sprite.h"

namespace FA {

namespace Entity {

template <class KeyT>
class AnimationPartWith : public BasicShapePart
{
public:
    static std::shared_ptr<AnimationPartWith<KeyT>> Create(const Shared::ImageAnimation &animation, bool center = true)
    {
        return std::make_shared<CtorHelper>(animation, center);
    }

    static std::shared_ptr<AnimationPartWith<KeyT>> Create(KeyT &lookupKey, bool center = true)
    {
        return std::make_shared<CtorHelper>(lookupKey, center);
    }

    virtual ~AnimationPartWith() = default;

    virtual void Enter() override
    {
        currentAnimation_ = GetAnimation(lookupKey_);
        currentAnimation_.Start();
    }

    virtual void Update(float deltaTime) override
    {
        currentAnimation_.Update(deltaTime);
        updateCB_(currentAnimation_);
    }

    virtual void ApplyTo(Graphic::SpriteIf &sprite) const override { currentAnimation_.ApplyTo(sprite, center_); }

    void RegisterAnimation(const KeyT key, const Shared::ImageAnimation &animation)
    {
        auto res = map_.emplace(key, animation);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::ImageAnimation &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for multiple animation, depending on KeyT */
    AnimationPartWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , defaultAnimation_(std::make_shared<Shared::Sequence<Shared::ImageFrame>>(1.0f))
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ImageAnimation &) {})
        , center_(center)
    {}

    /* Constructor for singel animation */
    AnimationPartWith(const Shared::ImageAnimation &animation, bool center = true)
        : lookupKey_(defaultKey_)
        , defaultAnimation_(animation)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ImageAnimation &) {})
        , center_(center)
    {
        RegisterAnimation(defaultKey_, animation);
    }

private:
    struct CtorHelper : public AnimationPartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey, bool center = true)
            : AnimationPartWith<KeyT>(lookupKey, center)
        {}

        CtorHelper(const Shared::ImageAnimation &animation, bool center = true)
            : AnimationPartWith<KeyT>(animation, center)
        {}
    };

    KeyT defaultKey_{};
    Shared::ImageAnimation defaultAnimation_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::ImageAnimation> map_;
    Shared::ImageAnimation currentAnimation_;
    std::function<void(const Shared::ImageAnimation &)> updateCB_;
    bool center_{};

private:
    Shared::ImageAnimation GetAnimation(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }

        LOG_ERROR("Could not find %s", DUMP(key));
        return defaultAnimation_;
    }
};

using AnimationPart = AnimationPartWith<int>;

}  // namespace Entity

}  // namespace FA
