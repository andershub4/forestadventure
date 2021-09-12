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
    CameraManager(sf::RenderTarget &renderTarget);
    ~CameraManager();

    void Track(const sf::Vector2f& position);
    void Update(const sf::Vector2u& mapSize);

private:
    sf::RenderTarget& renderTarget_;
    std::unique_ptr<Camera> camera_ = nullptr;
};

}  // namespace FA
