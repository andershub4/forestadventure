/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicTransition.h"

#include "EffectFactory.h"

namespace FA {

namespace Scene {

class FadeTransition : public BasicTransition
{
public:
    FadeTransition(CreateSceneFn nextSceneFn);
    virtual ~FadeTransition();

    virtual void Update(float deltaTime) { elapsedTime_ += deltaTime; }
    virtual bool IsFinished() const { return elapsedTime_ > duration_; }

    virtual std::unique_ptr<Shared::EffectIf> CreateEffect(const sf::Vector2f& position,
                                                           const sf::Vector2f& size) const override;

private:
    float elapsedTime_{0.0f};
    Shared::EffectFactory factory_;
};

}  // namespace Scene

}  // namespace FA
