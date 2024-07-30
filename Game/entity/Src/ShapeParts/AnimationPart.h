/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "BasicAnimationPart.h"
#include "Logging.h"

namespace FA {

namespace Entity {

template <class ValueT>
class SelectionBaseIf
{
public:
    virtual ~SelectionBaseIf() = default;
    virtual ValueT *Get() const = 0;
};

template <class ValueT>
class SingleSelection : public SelectionBaseIf<ValueT>
{
public:
    SingleSelection(std::shared_ptr<ValueT> selection)
        : selection_(selection)
    {}

    virtual ValueT *Get() const override { return selection_.get(); }

private:
    std::shared_ptr<ValueT> selection_;
};

template <class ValueT, class KeyT>
class MultiSelection : public SelectionBaseIf<ValueT>
{
    using SelectFn = std::function<ValueT *(const std::unordered_map<KeyT, std::shared_ptr<ValueT>> &)>;

public:
    MultiSelection(const KeyT *const key)
    {
        selectFn_ = [key](const std::unordered_map<KeyT, std::shared_ptr<ValueT>> &map) {
            bool found = map.find(*key) != map.end();
            ValueT *result = nullptr;

            if (found) {
                result = map.at(*key).get();
            }
            else {
                LOG_ERROR("%s can not be found", DUMP(key));
            }

            return result;
        };
    }

    void RegisterSelection(const KeyT &key, std::shared_ptr<ValueT> selection)
    {
        auto it = map_.find(key);
        if (it != map_.end()) {
            LOG_WARN("%s is already registered", DUMP(key));
        }
        else {
            map_.insert({key, selection});
        }
    }

    virtual ValueT *Get() const override { return selectFn_(map_); }

private:
    SelectFn selectFn_;
    std::unordered_map<KeyT, std::shared_ptr<ValueT>> map_;
};

template <class AnimationT>
class AnimationPart : public BasicAnimationPart
{
public:
    AnimationPart(std::shared_ptr<SelectionBaseIf<AnimationT>> selection)
        : selection_(selection)
    {}

    virtual ~AnimationPart() = default;

    virtual void Enter() override
    {
        currentAnimation_ = selection_->Get();
        currentAnimation_->Restart();
    }

    virtual void Update(float deltaTime) override { currentAnimation_->Update(deltaTime); }

    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const { currentAnimation_->DrawTo(renderTarget); }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_->SetPosition(position); }

    virtual void SetRotation(float angle) override { currentAnimation_->SetRotation(angle); }

    bool Intersects(const BasicAnimationPart &otherPart)
    {
        auto other = static_cast<const AnimationPart<AnimationT> &>(otherPart);
        return currentAnimation_->Intersects(*other.currentAnimation_);
    }

private:
    std::shared_ptr<SelectionBaseIf<AnimationT>> selection_;
    AnimationT *currentAnimation_{nullptr};
};

}  // namespace Entity

}  // namespace FA
