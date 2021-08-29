/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "Animation/Animator.h"
#include "BasicComponent.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class AnimationComponent : public BasicComponent
{
public:
    virtual void Update(float deltaTime) override;

    void AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation);
    void ApplyTo(sf::Sprite &sprite);
    void SetAnimation(FrameType frameType, FaceDirection faceDir);
    bool IsCompleted() const;

private:
    Animator animator_;
    Animation currentAnimation_;

private:
    std::string KeyStr(FrameType frameType, FaceDirection faceDir) const;
};

}  // namespace Entity

}  // namespace FA
