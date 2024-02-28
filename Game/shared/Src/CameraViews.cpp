/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "CameraViews.h"

#include <SFML/System/Vector2.hpp>

#include "CameraView.h"

namespace FA {

namespace Shared {

CameraViews::CameraViews() = default;

CameraViews::~CameraViews() = default;

void CameraViews::CreateCameraView(const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize, float zoomFactor)
{
    cameraView_ = std::make_unique<CameraView>(renderTargetSize, mapSize, zoomFactor);
}

void CameraViews::Update(float deltaTime)
{
    if (cameraView_) cameraView_->UpdatePosition(deltaTime);
}

CameraView& CameraViews::GetCameraView() const
{
    return *cameraView_.get();
}

}  // namespace Shared

}  // namespace FA
