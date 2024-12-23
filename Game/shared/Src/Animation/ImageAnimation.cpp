/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation/ImageAnimation.h"

#include "SpriteIf.h"

namespace FA {

namespace Shared {

ImageAnimation::ImageAnimation(std::shared_ptr<SequenceIf<ImageFrame>> seq)
    : seq_(seq)
{
    validSeq_ = !seq->IsEmpty();
}

void ImageAnimation::Update(float deltaTime)
{
    if (validSeq_) {
        seq_->Update(deltaTime);
        updateCB_(*this);
    }
}

void ImageAnimation::ApplyTo(std::shared_ptr<Graphic::DrawableIf> drawable) const
{
    auto sprite = std::dynamic_pointer_cast<Graphic::SpriteIf>(drawable);
    auto frame = seq_->GetCurrent();
    sprite->setTexture(*frame.texture_);
    sprite->setTextureRect(frame.rect_);
    if (center_) {
        sprite->setOrigin(frame.center_.x, frame.center_.y);
    }
}

void ImageAnimation::RegisterUpdateCB(std::function<void(const ImageAnimationIf&)> updateCB)
{
    updateCB_ = updateCB;
}

void ImageAnimation::Start()
{
    seq_->Start();
}

void ImageAnimation::Stop()
{
    seq_->Stop();
}

void ImageAnimation::Restart()
{
    seq_->Restart();
}

bool ImageAnimation::IsCompleted() const
{
    return seq_->IsCompleted();
}

void ImageAnimation::Center()
{
    center_ = true;
}

}  // namespace Shared

}  // namespace FA
