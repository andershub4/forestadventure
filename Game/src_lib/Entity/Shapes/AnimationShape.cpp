/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationShape.h"

namespace FA {

namespace Entity {

AnimationShape::AnimationShape(std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc)
    : lookupKeyFunc_(lookupKeyFunc)
{}

void AnimationShape::Update(float deltaTime)
{
    currentAnimation_.Update(deltaTime);
}

void AnimationShape::AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation)
{
    auto k = lookupKeyFunc_(frameType, faceDir);
    animator_.AddAnimation(k, animation);
}

void AnimationShape::ApplyTo(sf::Sprite &sprite)
{
    currentAnimation_.ApplyTo(sprite);
}

void AnimationShape::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    auto k = lookupKeyFunc_(frameType, faceDir);
    currentAnimation_ = animator_.GetAnimation(k);
    currentAnimation_.Start();
}

bool AnimationShape::IsCompleted() const
{
    return currentAnimation_.IsCompleted();
}

}  // namespace Entity

}  // namespace FA
