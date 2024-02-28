/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "CameraViewIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class CameraView : public CameraViewIf
{
public:
    CameraView(const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize, float zoomFactor);
    virtual ~CameraView();

    virtual void SetTrackPoint(const sf::Vector2f& trackingPoint) override;
    virtual void SetFixPoint(const sf::Vector2f& fixedPoint) override;
    virtual void UpdatePosition(float deltaTime) override;
    virtual sf::Vector2f GetPosition() const override;

private:
    const sf::Vector2f* trackingPoint_{nullptr};
    sf::Vector2f fixedPoint_{};
    sf::Vector2f minViewPosition_{};
    sf::Vector2f maxViewPosition_{};
    sf::Vector2f position_{};

private:
    sf::Vector2f CalcViewPosition(const sf::Vector2f& point) const;
    float Clamp(float value, float lower, float upper) const;
};

}  // namespace Shared

}  // namespace FA
