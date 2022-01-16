/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class Camera;

class CameraManager
{
public:
    CameraManager(const sf::Vector2u& renderTargetSize);
    ~CameraManager();

    void Track(const sf::Vector2f& trackingPoint);
    void Update(sf::RenderTarget& renderTarget);
    void SetMapSize(const sf::Vector2u& mapSize);
    sf::Vector2u GetMapSize() const;

private:
    sf::Vector2u renderTargetSize_{};
    sf::Vector2u mapSize_{10u, 10u};
    std::unique_ptr<Camera> camera_ = nullptr;
};

}  // namespace FA
