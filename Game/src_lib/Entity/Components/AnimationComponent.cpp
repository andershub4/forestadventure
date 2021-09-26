/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationComponent.h"

#include <sstream>

namespace FA {

namespace Entity {

AnimationComponent::AnimationComponent(ComponentHandler *owner)
    : BasicComponent(owner)
{}

void AnimationComponent::Update(float deltaTime)
{
    currentAnimation_.Update(deltaTime);
}

void AnimationComponent::AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation)
{
    auto k = KeyStr(frameType, faceDir);
    animator_.AddAnimation(k, animation);
}

void AnimationComponent::ApplyTo(sf::Sprite &sprite)
{
    currentAnimation_.ApplyTo(sprite);
}

void AnimationComponent::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    auto k = KeyStr(frameType, faceDir);
    currentAnimation_ = animator_.GetAnimation(k);
    currentAnimation_.Start();
}

bool AnimationComponent::IsCompleted() const
{
    return currentAnimation_.IsCompleted();
}

std::string AnimationComponent::KeyStr(FrameType frameType, FaceDirection faceDir) const
{
    std::stringstream ss;
    ss << frameType << "_" << faceDir;

    return ss.str();
}

}  // namespace Entity

}  // namespace FA
