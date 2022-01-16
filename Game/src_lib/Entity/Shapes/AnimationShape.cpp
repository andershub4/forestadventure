/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationShape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Logging.h"

namespace FA {

namespace Entity {

AnimationShape::AnimationShape(std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc)
    : lookupKeyFunc_(lookupKeyFunc)
{}

void AnimationShape::Update(float deltaTime)
{
    currentAnimation_.Update(deltaTime);
    currentAnimation_.ApplyTo(sprite_);
}

void AnimationShape::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void AnimationShape::AddAnimation(FrameType frameType, FaceDirection faceDir, const Animation &animation)
{
    auto key = lookupKeyFunc_(frameType, faceDir);
    AddAnimation(key, animation);
}

void AnimationShape::SetAnimation(FrameType frameType, FaceDirection faceDir)
{
    auto k = lookupKeyFunc_(frameType, faceDir);
    currentAnimation_ = GetAnimation(k);
    currentAnimation_.ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    currentAnimation_.Start();
}

void AnimationShape::SetTransform(const sf::Vector2f &position, float scale)
{
    sprite_.setPosition(position);
    sprite_.setScale(scale, scale);
}

bool AnimationShape::IsCompleted() const
{
    return currentAnimation_.IsCompleted();
}

void AnimationShape::AddAnimation(const std::string &key, const Animation &animation)
{
    auto it = animationMap_.find(key);
    if (it != animationMap_.end()) {
        LOG_WARN("key: ", key, " is already registered");
    }
    else {
        animationMap_[key] = animation;
    }
}

Animation AnimationShape::GetAnimation(const std::string &key) const
{
    auto it = animationMap_.find(key);
    if (it != animationMap_.end()) {
        return animationMap_.at(key);
    }
    else {
        LOG_ERROR("key: ", key, " does not exist");
        return Animation();
    }
}

}  // namespace Entity

}  // namespace FA
