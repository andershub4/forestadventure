/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "CameraManager.h"

#include "Camera.h"

namespace FA {

CameraManager::CameraManager(const sf::Vector2u& renderTargetSize)
    : renderTargetSize_(renderTargetSize)
{}

CameraManager::~CameraManager() = default;

void CameraManager::Track(const sf::Vector2f& trackingPoint, const sf::Vector2u& mapSize)
{
    camera_ = std::make_unique<Camera>(trackingPoint, renderTargetSize_, mapSize);
}

void CameraManager::Update(float deltaTime)
{
    if (camera_) camera_->UpdatePosition(deltaTime);
}

sf::View CameraManager::GetView() const
{
    if (camera_) return camera_->GetView();

    return {};
}

void CameraManager::Reset()
{
    if (camera_) camera_->Reset();
}

}  // namespace FA
