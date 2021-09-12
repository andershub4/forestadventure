/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "CameraManager.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "Camera.h"

namespace FA {

CameraManager::CameraManager(sf::RenderTarget &renderTarget)
    : renderTarget_(renderTarget)
{}

CameraManager::~CameraManager() = default;

void CameraManager::Track(const sf::Vector2f& position)
{
    auto size = renderTarget_.getSize();
    camera_ = std::make_unique<Camera>(position, size);
}

void CameraManager::Update(const sf::Vector2u& mapSize)
{
    if (camera_) camera_->UpdatePosition(renderTarget_, mapSize);
}

}  // namespace FA