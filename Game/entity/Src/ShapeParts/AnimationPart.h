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
    static std::shared_ptr<AnimationPartWith<KeyT>> Create(const Shared::ImageAnimation &animation)
    {
        return std::make_shared<CtorHelper>(animation);
    }

    static std::shared_ptr<AnimationPartWith<KeyT>> Create(KeyT &lookupKey)
    {
        return std::make_shared<CtorHelper>(lookupKey);
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

    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const { currentAnimation_.DrawTo(renderTarget); }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_.SetPosition(position); }

    virtual void SetRotation(float angle) override { currentAnimation_.SetRotation(angle); }

    bool Intersects(const BasicShapePart &otherPart)
    {
        auto other = static_cast<const AnimationPartWith<KeyT> &>(otherPart);
        return currentAnimation_.Intersects(other.currentAnimation_);
    }

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
    AnimationPartWith(KeyT &lookupKey)
        : lookupKey_(lookupKey)
        , defaultAnimation_(std::make_shared<Graphic::Sprite>(),
                            std::make_shared<Shared::Sequence<Shared::ImageFrame>>(1.0f))
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ImageAnimation &) {})
    {}

    /* Constructor for singel animation */
    AnimationPartWith(const Shared::ImageAnimation &animation)
        : lookupKey_(defaultKey_)
        , defaultAnimation_(animation)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::ImageAnimation &) {})
    {
        RegisterAnimation(defaultKey_, animation);
    }

private:
    struct CtorHelper : public AnimationPartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey)
            : AnimationPartWith<KeyT>(lookupKey)
        {}

        CtorHelper(const Shared::ImageAnimation &animation)
            : AnimationPartWith<KeyT>(animation)
        {}
    };

    KeyT defaultKey_{};
    Shared::ImageAnimation defaultAnimation_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::ImageAnimation> map_;
    Shared::ImageAnimation currentAnimation_;
    std::function<void(const Shared::ImageAnimation &)> updateCB_;

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
