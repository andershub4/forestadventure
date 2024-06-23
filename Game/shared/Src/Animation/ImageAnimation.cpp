/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation/ImageAnimation.h"

#include "Logging.h"
#include "SpriteIf.h"

namespace FA {

namespace Shared {

ImageAnimation::ImageAnimation(std::shared_ptr<SequenceIf<Frame>> seq)
    : seq_(seq)
{}

void ImageAnimation::Update(float deltaTime)
{
    seq_->Update(deltaTime);
}

void ImageAnimation::ApplyTo(Graphic::SpriteIf& sprite, bool center) const
{
    if (!seq_->IsEmpty()) {
        auto frame = seq_->GetCurrent();
        sprite.setTexture(*frame.texture_);
        sprite.setTextureRect(frame.rect_);
        if (center) {
            sprite.setOrigin(frame.center_.x, frame.center_.y);
        }
    }
}

void ImageAnimation::Start()
{
    seq_->Start();
}

void ImageAnimation::Stop()
{
    seq_->Stop();
}

bool ImageAnimation::IsCompleted() const
{
    return seq_->IsCompleted();
}

void ImageAnimation::AddFrame(const Frame& frame)
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
