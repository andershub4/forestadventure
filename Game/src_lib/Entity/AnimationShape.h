/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "Animation/Animator.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class EntityService;

class AnimationShape
{
public:
    AnimationShape(EntityService *owner);

    void Update(float deltaTime);
    void Init();

    void AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation);
    void ApplyTo(sf::Sprite &sprite);
    void SetAnimation(FrameType frameType, FaceDirection faceDir);
    bool IsCompleted() const;

private:
    Animator animator_;
    Animation currentAnimation_;
    EntityService *entityService_ = nullptr;

private:
    std::string KeyStr(FrameType frameType, FaceDirection faceDir) const;
};

}  // namespace Entity

}  // namespace FA
