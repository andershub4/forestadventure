/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class CameraViewIf
{
public:
    virtual ~CameraViewIf() = default;

    virtual void SetTrackPoint(const sf::Vector2f& trackingPoint) = 0;
    virtual void SetFixPoint(const sf::Vector2f& fixedPoint) = 0;
    virtual void UpdatePosition(float deltaTime) = 0;
    virtual sf::Vector2f GetPosition() const = 0;
};

}  // namespace Shared

}  // namespace FA
