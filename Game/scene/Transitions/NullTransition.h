/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicTransition.h"

namespace FA {

namespace Scene {

class NullTransition : public BasicTransition
{
public:
    NullTransition(CreateSceneFn nextSceneFn);
    virtual ~NullTransition();

    virtual std::unique_ptr<Shared::BasicEffect> CreateEffect(const sf::Vector2f& position,
                                                              const sf::Vector2f& size) const override;
};

}  // namespace Scene

}  // namespace FA
