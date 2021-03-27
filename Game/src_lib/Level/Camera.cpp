/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Camera.h"

#include <SFML/Graphics/RenderTexture.hpp>

#include "Constant/Screen.h"
#include "Entity/Components/Sprite/BasicSprite.h"
#include "Entity/Entities/BasicEntity.h"
#include "Level.h"

namespace FA {

Camera::Camera(const Level &level)
    : view_({constant::Screen::centerX_f, constant::Screen::centerY_f},
            {constant::Screen::width_f, constant::Screen::height_f})
    , level_(level)
{}

Camera::~Camera() = default;

void Camera::UpdatePosition(sf::RenderTarget& renderTarget)
{
    if (entity_) {
        auto p = entity_->GetPosition();
        auto viewPosition = CalcViewPosition(p);
        view_.setCenter(viewPosition);
        renderTarget.setView(view_);
    }
}

void Camera::Follow(Entity::BasicEntity* entity)
{
    entity_ = entity;
}

sf::Vector2f Camera::GetPosition() const
{
    return view_.getCenter();
}

sf::Vector2f Camera::GetViewSize() const
{
    return view_.getSize();
}

sf::Vector2f Camera::CalcViewPosition(const sf::Vector2f& position) const
{
    auto viewPosition = sf::Vector2f(position.x, position.y);

    if (position.x <= constant::Screen::centerX_f) {
        viewPosition.x = constant::Screen::centerX_f;
    }
    else if (position.x >= (level_.GetSize().x - constant::Screen::centerX_f)) {
        viewPosition.x = level_.GetSize().x - constant::Screen::centerX_f;
    }

    if (position.y <= constant::Screen::centerY_f) {
        viewPosition.y = constant::Screen::centerY_f;
    }
    else if (position.y >= (level_.GetSize().y - constant::Screen::centerY_f)) {
        viewPosition.y = level_.GetSize().y - constant::Screen::centerY_f;
    }

    return viewPosition;
}

}  // namespace FA
