/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationPartIf.h"

#include <functional>
#include <unordered_map>

#include "Logging.h"

namespace FA {

namespace Entity {

template <class AnimationT, template <class...> class AnimationPartIfT, typename... Args>
class AnimationPartBase : public AnimationPartIfT<Args...>
{
public:
    AnimationPartBase(std::shared_ptr<AnimationT> animation)
        : animation_(animation)
    {}

    AnimationPartBase() = default;

    virtual void Update(float deltaTime) override { animation_->Update(deltaTime); }

    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const override { animation_->DrawTo(renderTarget); }

    virtual void SetPosition(const sf::Vector2f &position) override { animation_->SetPosition(position); }

    virtual void SetRotation(float angle) override { animation_->SetRotation(angle); }

    virtual bool Intersects(const AnimationPartIf &otherPart) const override
    {
        const auto &other = static_cast<const AnimationPartBase<AnimationT, AnimationPartIfT, Args...> &>(otherPart);
        return animation_->Intersects(*other.animation_);
    }

protected:
    std::shared_ptr<AnimationT> animation_;
};

template <class AnimationT>
class SingleAnimationPartIf : public AnimationPartIf
{};

template <class AnimationT>
class SingleAnimationPart : public AnimationPartBase<AnimationT, SingleAnimationPartIf, AnimationT>
{
public:
    SingleAnimationPart(std::shared_ptr<AnimationT> animation)
        : AnimationPartBase<AnimationT, SingleAnimationPartIf, AnimationT>(animation)
    {}

    virtual void Enter() override { this->animation_->Restart(); }
};

template <class KeyT, class AnimationT>
class MultiAnimationPartIf : public AnimationPartIf
{
public:
    virtual void Register(const KeyT &key, std::shared_ptr<AnimationT> animation) = 0;
};

template <class KeyT, class AnimationT>
class MultiAnimationPart : public AnimationPartBase<AnimationT, MultiAnimationPartIf, KeyT, AnimationT>
{
    using SelectFn =
        std::function<std::shared_ptr<AnimationT>(const std::unordered_map<KeyT, std::shared_ptr<AnimationT>> &)>;

public:
    MultiAnimationPart(const KeyT *const key)
        : AnimationPartBase<AnimationT, MultiAnimationPartIf, KeyT, AnimationT>()
    {
        selectFn_ = [key](const std::unordered_map<KeyT, std::shared_ptr<AnimationT>> &map) {
            bool found = map.find(*key) != map.end();
            std::shared_ptr<AnimationT> result{};

            if (found) {
                result = map.at(*key);
            }
            else {
                LOG_ERROR("%s can not be found", DUMP(key));
            }

            return result;
        };
    }

    virtual void Enter() override
    {
        this->animation_ = selectFn_(map_);
        this->animation_->Restart();
    }

    virtual void Register(const KeyT &key, std::shared_ptr<AnimationT> animation) override
    {
        auto it = map_.find(key);
        if (it != map_.end()) {
            LOG_WARN("%s is already registered", DUMP(key));
        }
        else {
            map_.insert({key, animation});
        }
    }

private:
    SelectFn selectFn_;
    std::unordered_map<KeyT, std::shared_ptr<AnimationT>> map_;
};

}  // namespace Entity

}  // namespace FA
