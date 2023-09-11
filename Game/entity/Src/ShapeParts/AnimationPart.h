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
#include "IRenderTarget.h"
#include "Logging.h"
#include "Sprites/AnimationSprite.h"

namespace FA {

namespace Entity {

template <class KeyT>
class AnimationPartWith : public BasicShapePart
{
public:
    static std::shared_ptr<AnimationPartWith<KeyT>> Create(const Shared::AnimationSprite &animation, bool center = true)
    {
        return std::make_shared<CtorHelper<KeyT>>(animation, center);
    }

    static std::shared_ptr<AnimationPartWith<KeyT>> Create(KeyT &lookupKey, bool center = true)
    {
        return std::make_shared<CtorHelper<KeyT>>(lookupKey, center);
    }

    virtual ~AnimationPartWith() = default;

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
            if (center_) {
                currentAnimation_.Center();
            }
            updateCB_(currentAnimation_);
        }
    }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_.SetPosition(position); }
    virtual void SetRotation(float rot) override { currentAnimation_.SetRotation(rot); }
    virtual void DrawTo(Graphic::IRenderTarget &renderTarget) const override { currentAnimation_.DrawTo(renderTarget); }

    void RegisterAnimation(const KeyT key, const Shared::AnimationSprite &animation) { map_[key] = animation; }
    void RegisterUpdateCB(std::function<void(const Shared::AnimationSprite &)> updateCB) { updateCB_ = updateCB; }

protected:
    AnimationPartWith(KeyT &lookupKey, bool center = true)
        : lookupKey_(lookupKey)
        , updateCB_([](const Shared::AnimationSprite &) {})
        , center_(center)
    {}

    AnimationPartWith(const Shared::AnimationSprite &animation, bool center = true)
        : lookupKey_(defaultKey_)
        , updateCB_([](const Shared::AnimationSprite &) {})
        , center_(center)
    {
        RegisterAnimation(defaultKey_, animation);
    }

private:
    template <class KeyT>
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
        else {
            LOG_ERROR("Could not find %s", DUMP(key));
        }

        return {};
    }
};

using AnimationPart = AnimationPartWith<int>;

}  // namespace Entity

}  // namespace FA
