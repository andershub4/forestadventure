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
#include "Sprite.h"
#include "Sprites/AnimationSprite.h"

namespace FA {

namespace Entity {

template <class KeyT>
class AnimationPartWith : public BasicShapePart
{
public:
    static std::shared_ptr<AnimationPartWith<KeyT>> Create(const Shared::AnimationSprite &animation, bool center = true,
                                                           bool isCollidable = true)
    {
        return std::make_shared<CtorHelper>(animation, center, isCollidable);
    }

    static std::shared_ptr<AnimationPartWith<KeyT>> Create(KeyT &lookupKey, bool center = true,
                                                           bool isCollidable = true)
    {
        return std::make_shared<CtorHelper>(lookupKey, center, isCollidable);
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

    virtual void ApplyTo(Graphic::SpriteIf &sprite) const override
    {
        currentAnimation_.ApplyTo(sprite);

        if (center_) {
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        }
    }

    virtual bool IsCollidable() const override { return isCollidable_; }

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
    AnimationPartWith(KeyT &lookupKey, bool center = true, bool isCollidable = true)
        : lookupKey_(lookupKey)
        , defaultAnimation_(1.0f)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::AnimationSprite &) {})
        , center_(center)
        , isCollidable_(isCollidable)
    {}

    /* Constructor for singel animation */
    AnimationPartWith(const Shared::AnimationSprite &animation, bool center = true, bool isCollidable = true)
        : lookupKey_(defaultKey_)
        , defaultAnimation_(animation)
        , currentAnimation_(defaultAnimation_)
        , updateCB_([](const Shared::AnimationSprite &) {})
        , center_(center)
        , isCollidable_(isCollidable)
    {
        RegisterAnimation(defaultKey_, animation);
    }

private:
    struct CtorHelper : public AnimationPartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey, bool center = true, bool isCollidable = true)
            : AnimationPartWith<KeyT>(lookupKey, center, isCollidable)
        {}

        CtorHelper(const Shared::AnimationSprite &animation, bool center = true, bool isCollidable = true)
            : AnimationPartWith<KeyT>(animation, center, isCollidable)
        {}
    };

    KeyT defaultKey_{};
    Shared::AnimationSprite defaultAnimation_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::AnimationSprite> map_;
    Shared::AnimationSprite currentAnimation_;
    std::function<void(const Shared::AnimationSprite &)> updateCB_;
    bool center_{};
    bool isCollidable_{false};

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
