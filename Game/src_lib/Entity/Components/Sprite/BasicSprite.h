/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class Movement;

class BasicSprite
{
public:
    BasicSprite(unsigned int size);
    virtual ~BasicSprite();

    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual sf::Vector2f GetPosition() const = 0;
    virtual void Move(const Movement& movement) = 0;

    virtual void StartAnimation() {}
    virtual void SetAnimation(FrameType frameType, FaceDirection faceDir) {}
    virtual bool AnimationIsCompleted() const { return true; }

private:
    unsigned int size_{};
};

}  // namespace Entity

}  // namespace FA
