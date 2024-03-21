/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicShapePart.h"
#include "Logging.h"
#include "RenderTargetIf.h"
#include "Sprite.h"
#include "Sprites/AnimationSprite.h"

namespace FA {

namespace Entity {

template <class KeyT>
class AnimationPartWith : public BasicShapePart
{
public:
    static std::shared_ptr<AnimationPartWith<KeyT>> Create(const Shared::AnimationSprite &animation, bool center = true)
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
        if (center_) {
            currentAnimation_.Center();
        }
        updateCB_(currentAnimation_);
    }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_.SetPosition(position); }
    virtual void SetRotation(float rot) override { currentAnimation_.SetRotation(rot); }
    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const override
    {
        currentAnimation_.DrawTo(renderTarget);
    }

    void RegisterAnimation(const KeyT key, const Shared::AnimationSprite &animation)
    {
        auto res = map_.emplace(key, animation);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::AnimationSprite &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for multiple animation, depending on KeyT */
    AnimationPartWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , defaultAnimation_(std::shared_ptr<Graphic::Sprite>(), 0, 1.0f)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::AnimationSprite &) {})
        , center_(center)
    {}

    /* Constructor for singel animation */
    AnimationPartWith(const Shared::AnimationSprite &animation, bool center = true)
        : lookupKey_(defaultKey_)
        , defaultAnimation_(animation)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::AnimationSprite &) {})
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

        CtorHelper(const Shared::AnimationSprite &animation, bool center = true)
            : AnimationPartWith<KeyT>(animation, center)
        {}
    };

    KeyT defaultKey_{};
    Shared::AnimationSprite defaultAnimation_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::AnimationSprite> map_;
    Shared::AnimationSprite currentAnimation_;
    std::function<void(const Shared::AnimationSprite &)> updateCB_;
    bool center_{};

private:
    Shared::AnimationSprite GetAnimation(const KeyT &key)
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
