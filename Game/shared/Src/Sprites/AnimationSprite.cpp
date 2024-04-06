/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Sprites/AnimationSprite.h"

#include "Logging.h"
#include "SpriteIf.h"

namespace FA {

namespace Shared {

AnimationSprite::AnimationSprite(float switchTime)
    : BasicCoolSprite<AnimationSpriteIf>()
    , switchTime_(switchTime)
    , time_(0.0)
{}

void AnimationSprite::Update(float deltaTime)
{
    if (!isStopped_ && nFrames_ > 1) {
        time_ += deltaTime;

        if (time_ >= switchTime_) {
            time_ = 0.0;
            ++iFrame_ %= nFrames_;
            isCompleted_ = (iFrame_ == 0);
        }
    }
}

void AnimationSprite::ApplyTo(Graphic::SpriteIf& sprite) const
{
    if (nFrames_ >= 1) {
        sprite.setTexture(*frames_[iFrame_].texture_);
        sprite.setTextureRect(frames_[iFrame_].rect_);
    }
}

void AnimationSprite::Start()
{
    if (nFrames_ <= 0) {
        LOG_WARN("Can't start animation, no frames");
        isValid_ = false;
    }
    else {
        isStopped_ = false;
        isValid_ = true;
    }
}

void AnimationSprite::Stop()
{
    isStopped_ = true;
    iFrame_ = 0;
}

bool AnimationSprite::IsCompleted() const
{
    return isCompleted_;
}

void AnimationSprite::AddFrame(const Frame& frame)
{
    if (!isStopped_) {
        LOG_WARN("Can't add frame during animation");
        return;
    }

    isValid_ = frame.texture_ != nullptr && frame.rect_.width != 0 && frame.rect_.height != 0;

    if (isValid_) {
        frames_.push_back(frame);
        nFrames_ = frames_.size();
    }
    else {
        LOG_WARN("%s is invalid", DUMP(frame));
    }
}

}  // namespace Shared

}  // namespace FA
