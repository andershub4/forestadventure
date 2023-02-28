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
class AnimationSprite : public BasicSprite
{
public:
    AnimationSprite(std::function<KeyT()> keyFn, std::function<void(const Shared::Animation &)> updateFn,
                    bool center = true)
        : table_(keyFn)
        , updateFn_(updateFn)
        , center_(center)
    {}

    AnimationSprite(std::function<KeyT()> keyFn, bool center = true)
        : table_(keyFn)
        , updateFn_([](const Shared::Animation &) {})
        , center_(center)
    {}

    virtual ~AnimationSprite() = default;

    virtual void Enter() override
    {
        currentAnimation_ = table_.GetResource();
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
            updateFn_(currentAnimation_);
        }
    }

    void RegisterResource(const KeyT &key, const Shared::Animation &animation)
    {
        table_.RegisterResource(key, animation);
    }

private:
    ResourceTable<KeyT, Shared::Animation> table_;
    Shared::Animation currentAnimation_;
    std::function<void(const Shared::Animation &)> updateFn_;
    bool center_{};
};

}  // namespace Entity

}  // namespace FA
