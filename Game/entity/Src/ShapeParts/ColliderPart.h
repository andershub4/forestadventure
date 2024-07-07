/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "Animation/ColliderAnimation.h"
#include "BasicColliderPart.h"
#include "Logging.h"
#include "RectangleShape.h"
#include "Sequence.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ColliderPartWith : public BasicColliderPart
{
public:
    static std::shared_ptr<ColliderPartWith<KeyT>> Create(const Shared::ColliderAnimation &animation)
    {
        return std::make_shared<CtorHelper>(animation);
    }

    static std::shared_ptr<ColliderPartWith<KeyT>> Create(KeyT &lookupKey)
    {
        return std::make_shared<CtorHelper>(lookupKey);
    }

    virtual ~ColliderPartWith() = default;

    virtual void Enter() override
    {
        currentAnimation_ = GetAnimation(lookupKey_);
        currentAnimation_.Restart();
    }

    virtual void Update(float deltaTime) override
    {
        currentAnimation_.Update(deltaTime);
        updateCB_(currentAnimation_);
    }

    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const { currentAnimation_.DrawTo(renderTarget); }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_.SetPosition(position); }

    virtual void SetRotation(float angle) override { currentAnimation_.SetRotation(angle); }

    bool Intersects(const BasicColliderPart &otherPart)
    {
        auto other = static_cast<const ColliderPartWith<KeyT> &>(otherPart);
        return currentAnimation_.Intersects(other.currentAnimation_);
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
    ColliderPartWith(KeyT &lookupKey)
        : lookupKey_(lookupKey)
        , defaultAnimation_(std::make_shared<Graphic::RectangleShape>(),
                            std::make_shared<Shared::Sequence<Shared::ColliderFrame>>(1.0f))
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ColliderAnimation &) {})
    {}

    /* Constructor for singel animation */
    ColliderPartWith(const Shared::ColliderAnimation &animation)
        : lookupKey_(defaultKey_)
        , defaultAnimation_(animation)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ColliderAnimation &) {})
    {
        RegisterCollider(defaultKey_, animation);
    }

private:
    struct CtorHelper : public ColliderPartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey)
            : ColliderPartWith<KeyT>(lookupKey)
        {}

        CtorHelper(const Shared::ColliderAnimation &animation)
            : ColliderPartWith<KeyT>(animation)
        {}
    };

    KeyT defaultKey_{};
    Shared::ColliderAnimation defaultAnimation_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::ColliderAnimation> map_;
    Shared::ColliderAnimation currentAnimation_;
    std::function<void(const Shared::ColliderAnimation &)> updateCB_;

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
