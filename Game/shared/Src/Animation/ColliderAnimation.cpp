/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation/ColliderAnimation.h"

#include <SFML/Graphics/Rect.hpp>

#include "RectangleShapeIf.h"
#include "SfmlPrint.h"

namespace FA {

namespace Shared {

ColliderAnimation::ColliderAnimation(std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq)
    : seq_(seq)
{}

void ColliderAnimation::Update(float deltaTime)
{
    seq_->Update(deltaTime);
}

void ColliderAnimation::ApplyTo(Graphic::RectangleShapeIf& rectShape, bool center) const
{
    if (!seq_->IsEmpty()) {
        auto frame = seq_->GetCurrent();
        auto size = frame.size_;
        rectShape.setSize(size);
        if (center) {
            rectShape.setOrigin(frame.center_.x, frame.center_.y);
        }
    }
}

void ColliderAnimation::Start()
{
    seq_->Start();
}

void ColliderAnimation::Stop()
{
    seq_->Stop();
}

bool ColliderAnimation::IsCompleted() const
{
    return seq_->IsCompleted();
}

}  // namespace Shared

}  // namespace FA
