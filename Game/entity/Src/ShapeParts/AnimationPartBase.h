/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "AnimationPartIf.h"

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Entity {

template <template <class...> class AnimationPartIfT, class AnimationT, class... Args>
class AnimationPartBase : public AnimationPartIfT<AnimationT, Args...>
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
        const auto &other = static_cast<const AnimationPartBase<AnimationPartIfT, AnimationT, Args...> &>(otherPart);
        return animation_->Intersects(*other.animation_);
    }

protected:
    std::shared_ptr<AnimationT> animation_;
};

}  // namespace Entity

}  // namespace FA
