/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicColliderPart.h"
#include "Colliders/ColliderAnimation.h"
#include "Logging.h"
#include "RectangleShapeIf.h"
#include "Sequence.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ColliderPartWith : public BasicColliderPart
{
public:
    static std::shared_ptr<ColliderPartWith<KeyT>> Create(const Shared::ColliderAnimation &animation,
                                                          bool center = true)
    {
        return std::make_shared<CtorHelper>(animation, center);
    }

    static std::shared_ptr<ColliderPartWith<KeyT>> Create(KeyT &lookupKey, bool center = true)
    {
        return std::make_shared<CtorHelper>(lookupKey, center);
    }

    virtual ~ColliderPartWith() = default;

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

    virtual void ApplyTo(Graphic::RectangleShapeIf &rectShape) const override
    {
        currentAnimation_.ApplyTo(rectShape, center_);
    }

    void RegisterCollider(const KeyT key, const Shared::ColliderAnimation &animation)
    {
        auto res = map_.emplace(key, animation);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::ColliderAnimation &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for multiple colliders, depending on KeyT */
    ColliderPartWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , defaultAnimation_(std::make_shared<Shared::Sequence<Shared::ColliderFrame>>(1.0f))
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ColliderAnimation &) {})
        , center_(center)
    {}

    /* Constructor for singel animation */
    ColliderPartWith(const Shared::ColliderAnimation &animation, bool center = true)
        : lookupKey_(defaultKey_)
        , defaultAnimation_(animation)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ColliderAnimation &) {})
        , center_(center)
    {
        RegisterCollider(defaultKey_, animation);
    }

private:
    struct CtorHelper : public ColliderPartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey, bool center = true)
            : ColliderPartWith<KeyT>(lookupKey, center)
        {}

        CtorHelper(const Shared::ColliderAnimation &animation, bool center = true)
            : ColliderPartWith<KeyT>(animation, center)
        {}
    };

    KeyT defaultKey_{};
    Shared::ColliderAnimation defaultAnimation_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::ColliderAnimation> map_;
    Shared::ColliderAnimation currentAnimation_;
    std::function<void(const Shared::ColliderAnimation &)> updateCB_;
    bool center_{};

private:
    Shared::ColliderAnimation GetAnimation(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }

        LOG_ERROR("Could not find %s", DUMP(key));
        return defaultAnimation_;
    }
};

using ColliderPart = ColliderPartWith<int>;

}  // namespace Entity

}  // namespace FA
