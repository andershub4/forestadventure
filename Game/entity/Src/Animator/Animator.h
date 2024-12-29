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

#include "Animation/AnimationTraits.h"

namespace FA {

namespace Entity {

template <class FrameT, class KeyT = void>
class Animator : public AnimatorIf<FrameT>
{
    using Animation = std::shared_ptr<Shared::AnimationIf<FrameT>>;
    using DrawableType = typename Shared::AnimationTraits<FrameT>::DrawableT;
    using SelectFn = std::function<Animation(const std::unordered_map<KeyT, Animation> &)>;

public:
    Animator(DrawableType &drawable, SelectFn selectFn,
             const std::initializer_list<std::pair<const KeyT, Animation>> &selections)
        : drawable_(drawable)
        , selectFn_(selectFn)
        , updateCb_{[](const Shared::AnimationIf<FrameT> &) {}}
        , map_(selections)
    {}

    virtual void Enter() override
    {
        animation_ = selectFn_(map_);
        animation_->Restart();
    }

    virtual void Update(float deltaTime) override
    {
        animation_->Update(deltaTime);
        animation_->ApplyTo(drawable_);
        updateCb_(*animation_);
    }

    virtual void RegisterUpdateCb(std::function<void(const Shared::AnimationIf<FrameT> &animation)> updateCb) override
    {
        updateCb_ = updateCb;
    }

private:
    DrawableType &drawable_;
    Animation animation_;
    SelectFn selectFn_;
    std::unordered_map<KeyT, Animation> map_;
    std::function<void(const Shared::AnimationIf<FrameT> &)> updateCb_;
};

template <class FrameT>
class Animator<FrameT, void> : public AnimatorIf<FrameT>
{
    using Animation = std::shared_ptr<Shared::AnimationIf<FrameT>>;
    using DrawableType = typename Shared::AnimationTraits<FrameT>::DrawableT;

public:
    Animator(DrawableType &drawable, Animation animation)
        : drawable_(drawable)
        , animation_(animation)
        , updateCb_{[](const Shared::AnimationIf<FrameT> &) {}}
    {}

    virtual void Enter() override { animation_->Restart(); }

    virtual void Update(float deltaTime) override
    {
        animation_->Update(deltaTime);
        animation_->ApplyTo(drawable_);
        updateCb_(*animation_);
    }

    virtual void RegisterUpdateCb(std::function<void(const Shared::AnimationIf<FrameT> &animation)> updateCb) override
    {
        updateCb_ = updateCb;
    }

private:
    DrawableType &drawable_;
    Animation animation_;
    std::function<void(const Shared::AnimationIf<FrameT> &)> updateCb_;
};

}  // namespace Entity

}  // namespace FA
