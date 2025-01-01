/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <initializer_list>
#include <memory>
#include <unordered_map>
#include <utility>

#include "AnimatorIf.h"

// Include the traits here, so proper DrawableType can be derived in aliasing declarations
#include "Animation/ColliderTraits.h"
#include "Animation/ImageTraits.h"

namespace FA {

namespace Entity {

template <class FrameT, class KeyT = void>
class Animator : public AnimatorIf<FrameT>
{
    using Animation = std::shared_ptr<Shared::AnimationIf<FrameT>>;
    using DrawableType = AnimatorIf<FrameT>::DrawableType;
    using UpdateCb = AnimatorIf<FrameT>::UpdateCb;

public:
    Animator(DrawableType &drawable, const std::initializer_list<std::pair<const KeyT, Animation>> &selections,
             const KeyT &key, bool pollKeyEachUpdate = false)
        : drawable_(drawable)
        , updateCb_{[](DrawableType &drawable, const Shared::AnimationIf<FrameT> &) {}}
        , map_(selections)
        , key_(key)
        , currentKey_(key)
        , pollKeySetAnimation_{[]() {}}
    {
        if (pollKeyEachUpdate) {
            pollKeySetAnimation_ = [this]() {
                if (currentKey_ != key_) {
                    SetAnimation();
                    animation_->Restart();
                }
            };
        }
    }

    virtual void Enter() override
    {
        SetAnimation();
        animation_->Restart();
    }

    virtual void Update(float deltaTime) override
    {
        pollKeySetAnimation_();
        animation_->Update(deltaTime);
        animation_->ApplyTo(drawable_);
        updateCb_(drawable_, *animation_);
    }

    virtual void RegisterUpdateCb(UpdateCb updateCb) override { updateCb_ = updateCb; }

private:
    DrawableType &drawable_;
    Animation animation_;
    std::unordered_map<KeyT, Animation> map_;
    UpdateCb updateCb_;
    const KeyT &key_;
    KeyT currentKey_;
    std::function<void()> pollKeySetAnimation_;

private:
    void SetAnimation()
    {
        std::shared_ptr<Shared::AnimationIf<FrameT>> nullAnimation{};
        animation_ = nullAnimation;
        bool found = map_.find(key_) != map_.end();
        if (found) {
            currentKey_ = key_;
            animation_ = map_.at(key_);
        }
        else {
            LOG_ERROR("%s can not be found", DUMP(key_));
        }
    }
};

template <class FrameT>
class Animator<FrameT, void> : public AnimatorIf<FrameT>
{
    using Animation = std::shared_ptr<Shared::AnimationIf<FrameT>>;
    using DrawableType = AnimatorIf<FrameT>::DrawableType;
    using UpdateCb = AnimatorIf<FrameT>::UpdateCb;

public:
    Animator(DrawableType &drawable, Animation animation)
        : drawable_(drawable)
        , animation_(animation)
        , updateCb_{[](DrawableType &drawable, const Shared::AnimationIf<FrameT> &) {}}
    {}

    virtual void Enter() override { animation_->Restart(); }

    virtual void Update(float deltaTime) override
    {
        animation_->Update(deltaTime);
        animation_->ApplyTo(drawable_);
        updateCb_(drawable_, *animation_);
    }

    virtual void RegisterUpdateCb(UpdateCb updateCb) override { updateCb_ = updateCb; }

private:
    DrawableType &drawable_;
    Animation animation_;
    UpdateCb updateCb_;
};

}  // namespace Entity

}  // namespace FA
