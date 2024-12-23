/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation/ColliderAnimation.h"

#include "RectangleShapeIf.h"

namespace FA {

namespace Shared {

ColliderAnimation::ColliderAnimation(std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq)
    : seq_(seq)
{
    validSeq_ = !seq->IsEmpty();
}

void ColliderAnimation::Update(float deltaTime)
{
    if (validSeq_) {
        seq_->Update(deltaTime);
        updateCB_(*this);
    }
}

void ColliderAnimation::ApplyTo(std::shared_ptr<Graphic::DrawableIf> drawable) const
{
    auto rectShape = std::dynamic_pointer_cast<Graphic::RectangleShapeIf>(drawable);
    auto frame = seq_->GetCurrent();
    rectShape->setSize(frame.size_);
    if (center_) {
        rectShape->setOrigin(frame.center_.x, frame.center_.y);
    }
}

void ColliderAnimation::RegisterUpdateCB(std::function<void(const ColliderAnimationIf &)> updateCB)
{
    updateCB_ = updateCB;
}

void ColliderAnimation::Start()
{
    seq_->Start();
}

void ColliderAnimation::Stop()
{
    seq_->Stop();
}

void ColliderAnimation::Restart()
{
    seq_->Restart();
}

bool ColliderAnimation::IsCompleted() const
{
    return seq_->IsCompleted();
}

void ColliderAnimation::Center()
{
    center_ = true;
}

}  // namespace Shared

}  // namespace FA
