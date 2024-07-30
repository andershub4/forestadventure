/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationPartIf.h"

#include "Selections/SelectionBaseIf.h"

namespace FA {

namespace Entity {

template <class AnimationT>
class AnimationPart : public AnimationPartIf
{
public:
    AnimationPart(std::shared_ptr<SelectionBaseIf<AnimationT>> selection)
        : selection_(selection)
    {}

    virtual void Enter() override
    {
        currentAnimation_ = selection_->Get();
        currentAnimation_->Restart();
    }

    virtual void Update(float deltaTime) override { currentAnimation_->Update(deltaTime); }

    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const override { currentAnimation_->DrawTo(renderTarget); }

    virtual void SetPosition(const sf::Vector2f &position) override { currentAnimation_->SetPosition(position); }

    virtual void SetRotation(float angle) override { currentAnimation_->SetRotation(angle); }

    virtual bool Intersects(const AnimationPartIf &otherPart) override
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
