/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>

#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

class ImageAnimationIf
{
public:
    virtual ~ImageAnimationIf() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const = 0;
    virtual bool Intersects(const ImageAnimationIf &other) const = 0;
    virtual void RegisterUpdateCB(std::function<void(const ImageAnimationIf &)> updateCB) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Restart() = 0;
    virtual bool IsCompleted() const = 0;
    virtual void Center() = 0;
    virtual void SetPosition(const sf::Vector2f &position) = 0;
    virtual void SetRotation(float angle) = 0;
};

}  // namespace Shared

}  // namespace FA
