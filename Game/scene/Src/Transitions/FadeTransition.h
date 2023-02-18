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

    virtual std::unique_ptr<Shared::BasicEffect> CreateEffect(const sf::Vector2f& position,
                                                              const sf::Vector2f& size) const override;

private:
    Shared::EffectFactory factory_;
};

}  // namespace Scene

}  // namespace FA
