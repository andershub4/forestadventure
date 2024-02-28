/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class CameraView;

class CameraViews
{
public:
    CameraViews();
    ~CameraViews();

    void CreateCameraView(const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize, float zoomFactor);
    void Update(float deltaTime);
    CameraView& GetCameraView() const;

private:
    std::unique_ptr<CameraView> cameraView_ = nullptr;
};

}  // namespace Shared

}  // namespace FA
