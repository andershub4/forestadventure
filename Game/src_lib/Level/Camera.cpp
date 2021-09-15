/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Camera.h"

#include <algorithm>

#include <SFML/Graphics/RenderTexture.hpp>

namespace FA {

Camera::Camera(const sf::Vector2f& position, const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize)
    : position_(position)
    , mapSize_(mapSize)
{
    auto size_f = static_cast<sf::Vector2f>(renderTargetSize);
    view_.setSize(size_f);
    centerPos_ = size_f / 2.0f;
    minViewPosition_ = {centerPos_.x, centerPos_.y};
    maxViewPosition_ = {mapSize_.x - centerPos_.x, mapSize_.y - centerPos_.y};
}

Camera::~Camera() = default;

void Camera::UpdatePosition(sf::RenderTarget& renderTarget)
{
    auto viewPosition = CalcViewPosition(position_);
    view_.setCenter(viewPosition);
    renderTarget.setView(view_);
}

sf::Vector2f Camera::CalcViewPosition(const sf::Vector2f& position) const
{
    sf::Vector2f viewPosition;
    viewPosition.x = Clamp(position.x, minViewPosition_.x, maxViewPosition_.x);
    viewPosition.y = Clamp(position.y, minViewPosition_.y, maxViewPosition_.y);

    return viewPosition;
}

float Camera::Clamp(float value, float lower, float upper) const
{
    return std::max(lower, std::min(value, upper));
}

}  // namespace FA
