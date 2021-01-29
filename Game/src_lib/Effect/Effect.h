/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class Effect
{
public:
    Effect(const sf::Vector2f& size);
    virtual ~Effect();

    virtual void DrawTo(sf::RenderTarget& renderTarget) const = 0;
    virtual void Update(float deltaTime) = 0;
    virtual bool IsFinished() const = 0;

private:
    sf::Vector2f size_;
};

}  // namespace FA
