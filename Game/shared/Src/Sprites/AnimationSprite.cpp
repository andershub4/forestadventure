/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/AnimationSprite.h"

#include "Sprite.h"

namespace FA {

namespace Shared {

AnimationSprite::AnimationSprite(std::shared_ptr<Graphic::ISprite> sprite, unsigned int defaultIndex, float switchTime)
    : BasicSprite(sprite)
    , switchTime_(switchTime)
    , time_(0.0)
    , defaultIndex_(defaultIndex)
    , iFrame_(defaultIndex)
{}

void AnimationSprite::Update(float deltaTime)
{
    if (!isStopped_ && nFrames_ > 1) {
        time_ += deltaTime;

        while (time_ >= switchTime_) {
            time_ -= switchTime_;
            ++iFrame_ %= nFrames_;
            isCompleted_ = (iFrame_ == 0);
        }
    }
    sprite_->setTexture(*frames_[iFrame_].texture_);
    sprite_->setTextureRect(frames_[iFrame_].rect_);
}

void AnimationSprite::Start()
{
    isStopped_ = false;
}

void AnimationSprite::Stop()
{
    isStopped_ = true;
    iFrame_ = defaultIndex_;
}

bool AnimationSprite::IsCompleted() const
{
    return isCompleted_;
}

void AnimationSprite::AddFrame(const Frame& frame)
{
    frames_.push_back(frame);
    nFrames_ = frames_.size();
}

}  // namespace Shared

}  // namespace FA
