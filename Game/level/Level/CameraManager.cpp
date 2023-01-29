/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "CameraManager.h"

#include <SFML/System/Vector2.hpp>

#include "Camera.h"

namespace FA {

CameraManager::CameraManager() = default;

CameraManager::~CameraManager() = default;

void CameraManager::CreateCamera(const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize)
{
    camera_ = std::make_unique<Camera>(renderTargetSize, mapSize);
}

void CameraManager::Update(float deltaTime)
{
    if (camera_) camera_->UpdatePosition(deltaTime);
}

Camera& CameraManager::GetCamera() const
{
    return *camera_.get();
}

}  // namespace FA
