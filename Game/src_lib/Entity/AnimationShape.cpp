/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationShape.h"

#include <sstream>

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/EntityService.h"

namespace FA {

namespace Entity {

AnimationShape::AnimationShape(EntityService *owner)
    : entityService_(owner)
{}

void AnimationShape::Update(float deltaTime)
{
    currentAnimation_.Update(deltaTime);
}

void AnimationShape::Init()
{
    auto dirs = entityService_->GetAttribute<FaceDirectionAttribute>()->GetAvailableDirections();

    for (auto frameType : entityService_->GetFrameTypes()) {
        if (frameType == FrameType::Undefined) continue;
        for (auto faceDir : dirs) {
            auto animation = entityService_->GetAnimation(frameType, faceDir);
            AddAnimation(frameType, faceDir, animation);
        }
    }
}

void AnimationShape::AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation)
{
    auto k = KeyStr(frameType, faceDir);
    animator_.AddAnimation(k, animation);
}

void AnimationShape::ApplyTo(sf::Sprite &sprite)
{
    currentAnimation_.ApplyTo(sprite);
}

void AnimationShape::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    auto k = KeyStr(frameType, faceDir);
    currentAnimation_ = animator_.GetAnimation(k);
    currentAnimation_.Start();
}

bool AnimationShape::IsCompleted() const
{
    return currentAnimation_.IsCompleted();
}

std::string AnimationShape::KeyStr(FrameType frameType, FaceDirection faceDir) const
{
    std::stringstream ss;
    ss << frameType << "_" << faceDir;

    return ss.str();
}

}  // namespace Entity

}  // namespace FA
