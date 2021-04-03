/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Fwd/SfmlFwd.h"

namespace FA {

enum class FrameType;
enum class FaceDirection;

namespace Entity {

class Movement;

class BasicSprite
{
public:
    BasicSprite();
    virtual ~BasicSprite();

    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual sf::Vector2f GetPosition() const = 0;
    virtual void Move(const Movement& movement) = 0;

    virtual void StartAnimation() {}
    virtual void SetAnimation(FrameType frameType, FaceDirection faceDir) {}
    virtual bool AnimationIsCompleted() const { return true; }
};

}  // namespace Entity

}  // namespace FA
