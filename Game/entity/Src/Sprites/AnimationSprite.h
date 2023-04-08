/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>

#include "BasicSprite.h"
#include "Logging.h"
#include "Resource/Animation.h"

namespace FA {

namespace Entity {

template <class KeyT>
class AnimationSpriteWith : public BasicSprite
{
public:
    static std::shared_ptr<AnimationSpriteWith<KeyT>> Create(const Shared::Animation &animation, bool center = true)
    {
        return std::make_shared<CtorHelper<KeyT>>(animation, center);
    }

    static std::shared_ptr<AnimationSpriteWith<KeyT>> Create(KeyT &lookupKey, bool center = true)
    {
        return std::make_shared<CtorHelper<KeyT>>(lookupKey, center);
    }

    virtual ~AnimationSpriteWith() = default;

    virtual void Enter() override
    {
        currentAnimation_ = GetAnimation(lookupKey_);

        if (currentAnimation_.IsValid()) {
            currentAnimation_.Start();
        }
    }

    virtual void Update(float deltaTime) override
    {
        if (currentAnimation_.IsValid()) {
            currentAnimation_.Update(deltaTime);
            currentAnimation_.ApplyTo(sprite_);
            if (center_) {
                sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
            }
            updateCB_(currentAnimation_);
        }
    }

    void RegisterAnimation(const KeyT key, const Shared::Animation &animation) { map_[key] = animation; }
    void RegisterUpdateCB(std::function<void(const Shared::Animation &)> updateCB) { updateCB_ = updateCB; }

protected:
    AnimationSpriteWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , updateCB_([](const Shared::Animation &) {})
        , center_(center)
    {}

    AnimationSpriteWith(const Shared::Animation &animation, bool center = true)
        : lookupKey_(defaultKey_)
        , updateCB_([](const Shared::Animation &) {})
        , center_(center)
    {
        RegisterAnimation(defaultKey_, animation);
    }

private:
    template <class KeyT>
    struct CtorHelper : public AnimationSpriteWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey, bool center = true)
            : AnimationSpriteWith<KeyT>(lookupKey, center)
        {}

        CtorHelper(const Shared::Animation &animation, bool center = true)
            : AnimationSpriteWith<KeyT>(animation, center)
        {}
    };

    KeyT defaultKey_{};
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::Animation> map_;
    Shared::Animation currentAnimation_;
    std::function<void(const Shared::Animation &)> updateCB_;
    bool center_{};

private:
    Shared::Animation GetAnimation(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }
        else {
            std::stringstream ss;
            ss << key;
            LOG_ERROR("Could not find key: %s", ss.str().c_str());
        }

        return {};
    }
};

using AnimationSprite = AnimationSpriteWith<int>;

}  // namespace Entity

}  // namespace FA
