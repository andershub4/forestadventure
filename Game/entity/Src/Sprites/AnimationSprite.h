/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicSprite.h"
#include "Resource/Animation.h"
#include "ResourceTable.h"

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
        currentAnimation_ = table_.GetResource(lookupKey_);
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

    ResourceTable<KeyT, Shared::Animation> &Table() { return table_; }

    void RegisterUpdateCB(std::function<void(const Shared::Animation &)> updateCB) { updateCB_ = updateCB; }

protected:
    AnimationSpriteWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , updateCB_([](const Shared::Animation &) {})
        , center_(center)
    {}

    AnimationSpriteWith(const Shared::Animation &animation, bool center = true)
        : lookupKey_(defaultKey)
        , updateCB_([](const Shared::Animation &) {})
        , center_(center)
    {
        table_.RegisterResource(defaultKey, animation);
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

    KeyT defaultKey{};
    KeyT &lookupKey_;
    ResourceTable<KeyT, Shared::Animation> table_;
    Shared::Animation currentAnimation_;
    std::function<void(const Shared::Animation &)> updateCB_;
    bool center_{};
};

using AnimationSprite = AnimationSpriteWith<int>;

}  // namespace Entity

}  // namespace FA
