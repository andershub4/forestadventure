/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "CameraView.h"

#include <algorithm>

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Shared {

CameraView::CameraView(const sf::Vector2u& viewSize, const sf::Vector2u& mapSize, float zoomFactor)
{
    sf::Vector2f size = static_cast<sf::Vector2f>(viewSize);
    auto centerPos = size / (2.0f * (1 / zoomFactor));
    minViewPosition_ = {centerPos.x, centerPos.y};
    maxViewPosition_ = {mapSize.x - centerPos.x, mapSize.y - centerPos.y};
}

CameraView::~CameraView() = default;

void CameraView::SetTrackPoint(const sf::Vector2f& trackingPoint)
{
    trackingPoint_ = &trackingPoint;
    position_ = CalcViewPosition(*trackingPoint_);
}

void CameraView::SetFixPoint(const sf::Vector2f& fixedPoint)
{
    fixedPoint_ = fixedPoint;
    trackingPoint_ = &fixedPoint_;
    position_ = CalcViewPosition(*trackingPoint_);
}

void CameraView::UpdatePosition(float deltaTime)
{
    position_ = trackingPoint_ ? CalcViewPosition(*trackingPoint_) : sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f CameraView::GetPosition() const
{
    return position_;
}

sf::Vector2f CameraView::CalcViewPosition(const sf::Vector2f& point) const
{
    sf::Vector2f viewPosition;
    viewPosition.x = Clamp(point.x, minViewPosition_.x, maxViewPosition_.x);
    viewPosition.y = Clamp(point.y, minViewPosition_.y, maxViewPosition_.y);

    return viewPosition;
}

float CameraView::Clamp(float value, float lower, float upper) const
{
    return std::max(lower, std::min(value, upper));
}

}  // namespace Shared

}  // namespace FA
