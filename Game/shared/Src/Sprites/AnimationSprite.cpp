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

AnimationSprite::AnimationSprite(std::shared_ptr<SequenceIf<Frame>> seq)
    : seq_(seq)
{}

void AnimationSprite::Update(float deltaTime)
{
    seq_->Update(deltaTime);
}

void AnimationSprite::ApplyTo(Graphic::SpriteIf& sprite, bool center) const
{
    auto frame = seq_->GetCurrent();
    if (frame != InvalidFrame) {
        sprite.setTexture(*frame.texture_);
        sprite.setTextureRect(frame.rect_);
        if (center) {
            sprite.setOrigin(frame.center_.x, frame.center_.y);
        }
    }
}

void AnimationSprite::Start()
{
    seq_->Start();
}

void AnimationSprite::Stop()
{
    seq_->Stop();
}

bool AnimationSprite::IsCompleted() const
{
    return seq_->IsCompleted();
}

void AnimationSprite::AddFrame(const Frame& frame)
{
    bool isValid = frame.texture_ != nullptr && frame.rect_.width != 0 && frame.rect_.height != 0;

    if (isValid) {
        seq_->Add(frame);
    }
    else {
        LOG_WARN("%s is invalid", DUMP(frame));
    }
}

}  // namespace Shared

}  // namespace FA
