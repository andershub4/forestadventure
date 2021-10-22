/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>

#include "Animation/Animator.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class AnimationShape
{
public:
    AnimationShape(std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc);

    void Update(float deltaTime);

    void AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation);
    void ApplyTo(sf::Sprite &sprite);
    void SetAnimation(FrameType frameType, FaceDirection faceDir);
    bool IsCompleted() const;

private:
    Animator animator_;
    Animation currentAnimation_;
    std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc_;
};

}  // namespace Entity

}  // namespace FA
