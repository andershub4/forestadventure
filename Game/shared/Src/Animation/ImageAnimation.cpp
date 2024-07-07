/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation/ImageAnimation.h"

#include "RenderTargetIf.h"
#include "SpriteIf.h"

namespace FA {

namespace Shared {

ImageAnimation::ImageAnimation(std::shared_ptr<Graphic::SpriteIf> sprite, std::shared_ptr<SequenceIf<ImageFrame>> seq)
    : sprite_(sprite)
    , seq_(seq)
{
    validSeq_ = !seq->IsEmpty();
}

void ImageAnimation::Update(float deltaTime)
{
    if (validSeq_) {
        seq_->Update(deltaTime);
        auto frame = seq_->GetCurrent();
        sprite_->setTexture(*frame.texture_);
        sprite_->setTextureRect(frame.rect_);
        if (center_) {
            sprite_->setOrigin(frame.center_.x, frame.center_.y);
        }
    }
}

void ImageAnimation::DrawTo(Graphic::RenderTargetIf& renderTarget) const
{
    renderTarget.draw(*sprite_);
}

bool ImageAnimation::Intersects(const ImageAnimationIf& other) const
{
    auto otherImpl = static_cast<const ImageAnimation&>(other);
    return sprite_->getGlobalBounds().intersects(otherImpl.sprite_->getGlobalBounds());
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

void ImageAnimation::Center()
{
    center_ = true;
}

void ImageAnimation::SetPosition(const sf::Vector2f& position)
{
    sprite_->setPosition(position);
}

void ImageAnimation::SetRotation(float angle)
{
    sprite_->setRotation(angle);
}
}  // namespace Shared

}  // namespace FA
