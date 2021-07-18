/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Camera.h"

#include <SFML/Graphics/RenderTexture.hpp>

#include "Entity/Entities/BasicEntity.h"

namespace FA {

Camera::Camera(const sf::Vector2u& size)
{
    auto size_f = static_cast<sf::Vector2f>(size);
    view_.setSize(size_f);
    centerPos_ = size_f / 2.0f;
}

Camera::~Camera() = default;

void Camera::UpdatePosition(sf::RenderTarget& renderTarget, const sf::Vector2u& mapSize)
{
    if (entity_) {
        auto p = entity_->GetPosition();
        auto viewPosition = CalcViewPosition(p, mapSize);
        view_.setCenter(viewPosition);
        renderTarget.setView(view_);
    }
}

void Camera::Follow(Entity::BasicEntity* entity)
{
    entity_ = entity;
}

sf::Vector2f Camera::CalcViewPosition(const sf::Vector2f& position, const sf::Vector2u& mapSize) const
{
    auto viewPosition = sf::Vector2f(position.x, position.y);

    if (position.x <= centerPos_.x) {
        viewPosition.x = centerPos_.x;
    }
    else if (position.x >= (mapSize.x - centerPos_.x)) {
        viewPosition.x = mapSize.x - centerPos_.x;
    }

    if (position.y <= centerPos_.y) {
        viewPosition.y = centerPos_.y;
    }
    else if (position.y >= (mapSize.y - centerPos_.y)) {
        viewPosition.y = mapSize.y - centerPos_.y;
    }

    return viewPosition;
}

}  // namespace FA
