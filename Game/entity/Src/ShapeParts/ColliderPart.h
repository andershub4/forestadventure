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
#include "Colliders/Collider.h"
#include "Logging.h"
#include "RectangleShapeIf.h"
#include "Sequence.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ColliderPartWith : public BasicColliderPart
{
public:
    static std::shared_ptr<ColliderPartWith<KeyT>> Create(const Shared::Collider &collider, bool center = true)
    {
        return std::make_shared<CtorHelper>(collider, center);
    }

    static std::shared_ptr<ColliderPartWith<KeyT>> Create(KeyT &lookupKey, bool center = true)
    {
        return std::make_shared<CtorHelper>(lookupKey, center);
    }

    virtual ~ColliderPartWith() = default;

    virtual void Enter() override
    {
        currentCollider_ = GetCollider(lookupKey_);
        currentCollider_.Start();
    }

    virtual void Update(float deltaTime) override
    {
        currentCollider_.Update(deltaTime);
        updateCB_(currentCollider_);
    }

    virtual void ApplyTo(Graphic::RectangleShapeIf &rectShape) const override
    {
        currentCollider_.ApplyTo(rectShape, center_);
    }

    void RegisterCollider(const KeyT key, const Shared::Collider &collider)
    {
        auto res = map_.emplace(key, collider);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::Collider &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for multiple colliders, depending on KeyT */
    ColliderPartWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , defaultCollider_(std::make_shared<Shared::Sequence<Shared::ColliderFrame>>(1.0f))
        , currentCollider_(defaultCollider_)
        , updateCB_([](const Shared::Collider &) {})
        , center_(center)
    {}

    /* Constructor for singel animation */
    ColliderPartWith(const Shared::Collider &collider, bool center = true)
        : lookupKey_(defaultKey_)
        , defaultCollider_(collider)
        , currentCollider_(defaultCollider_)
        , updateCB_([](const Shared::Collider &) {})
        , center_(center)
    {
        RegisterCollider(defaultKey_, collider);
    }

private:
    struct CtorHelper : public ColliderPartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey, bool center = true)
            : ColliderPartWith<KeyT>(lookupKey, center)
        {}

        CtorHelper(const Shared::Collider &collider, bool center = true)
            : ColliderPartWith<KeyT>(collider, center)
        {}
    };

    KeyT defaultKey_{};
    Shared::Collider defaultCollider_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::Collider> map_;
    Shared::Collider currentCollider_;
    std::function<void(const Shared::Collider &)> updateCB_;
    bool center_{};

private:
    Shared::Collider GetCollider(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }

        LOG_ERROR("Could not find %s", DUMP(key));
        return defaultCollider_;
    }
};

using ColliderPart = ColliderPartWith<int>;

}  // namespace Entity

}  // namespace FA
