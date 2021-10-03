/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationAttribute.h"

#include <sstream>

namespace FA {

namespace Entity {

AnimationAttribute::AnimationAttribute(PropertyHandler *owner)
    : BasicAttribute(owner)
{}

void AnimationAttribute::Update(float deltaTime)
{
    currentAnimation_.Update(deltaTime);
}

void AnimationAttribute::AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation)
{
    auto k = KeyStr(frameType, faceDir);
    animator_.AddAnimation(k, animation);
}

void AnimationAttribute::ApplyTo(sf::Sprite &sprite)
{
    currentAnimation_.ApplyTo(sprite);
}

void AnimationAttribute::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    auto k = KeyStr(frameType, faceDir);
    currentAnimation_ = animator_.GetAnimation(k);
    currentAnimation_.Start();
}

bool AnimationAttribute::IsCompleted() const
{
    return currentAnimation_.IsCompleted();
}

std::string AnimationAttribute::KeyStr(FrameType frameType, FaceDirection faceDir) const
{
    std::stringstream ss;
    ss << frameType << "_" << faceDir;

    return ss.str();
}

}  // namespace Entity

}  // namespace FA
