/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Fwd/SfmlFwd.h"

namespace FA {

class Camera;

class CameraManager
{
public:
    CameraManager();
    ~CameraManager();

    void CreateCamera(const sf::Vector2u& renderTargetSize, const sf::Vector2u& mapSize);
    void Update(float deltaTime);
    Camera& GetCamera() const;

private:
    std::unique_ptr<Camera> camera_ = nullptr;
};

}  // namespace FA
