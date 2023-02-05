/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Camera.h"

#include <SFML/System/Vector2.hpp>

#include <algorithm>

namespace FA {

namespace Shared {

Camera::Camera(const sf::Vector2u& viewSize, const sf::Vector2u& mapSize)
{
    auto size_f = static_cast<sf::Vector2f>(viewSize);
    const float zoomFactor = 0.5;
    view_.setSize(size_f);
    view_.zoom(zoomFactor);
    auto centerPos = size_f / (2.0f * (1 / zoomFactor));
    minViewPosition_ = {centerPos.x, centerPos.y};
    maxViewPosition_ = {mapSize.x - centerPos.x, mapSize.y - centerPos.y};
}

Camera::~Camera() = default;

void Camera::Track(const sf::Vector2f& trackingPoint)
{
    trackingPoint_ = &trackingPoint;
}

void Camera::UpdatePosition(float deltaTime)
{
    auto viewPosition = trackingPoint_ ? CalcViewPosition() : sf::Vector2f(0.0f, 0.0f);
    view_.setCenter(viewPosition);
}

sf::View Camera::GetView() const
{
    return view_;
}

sf::Vector2f Camera::CalcViewPosition() const
{
    sf::Vector2f viewPosition;
    viewPosition.x = Clamp(trackingPoint_->x, minViewPosition_.x, maxViewPosition_.x);
    viewPosition.y = Clamp(trackingPoint_->y, minViewPosition_.y, maxViewPosition_.y);

    return viewPosition;
}

float Camera::Clamp(float value, float lower, float upper) const
{
    return std::max(lower, std::min(value, upper));
}

}  // namespace Shared

}  // namespace FA
