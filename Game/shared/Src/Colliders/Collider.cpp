/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Colliders/Collider.h"

#include <SFML/Graphics/Rect.hpp>

#include "Logging.h"
#include "RectangleShapeIf.h"
#include "SfmlPrint.h"

namespace FA {

namespace Shared {

Collider::Collider(std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq)
    : seq_(seq)
{}

void Collider::Update(float deltaTime)
{
    seq_->Update(deltaTime);
}

void Collider::ApplyTo(Graphic::RectangleShapeIf& rectShape, bool center) const
{
    auto frame = seq_->GetCurrent();
    auto size = frame.size_;
    if (size != sf::Vector2f{}) {
        rectShape.setSize(size);
        if (center) {
            rectShape.setOrigin(frame.center_.x, frame.center_.y);
        }
    }
}

void Collider::Start()
{
    seq_->Start();
}

void Collider::Stop()
{
    seq_->Stop();
}

bool Collider::IsCompleted() const
{
    return seq_->IsCompleted();
}

void Collider::AddRect(const Shared::ColliderFrame& frame)
{
    bool isValid = frame != InvalidColliderFrame;

    if (isValid) {
        seq_->Add(frame);
    }
    else {
        LOG_WARN("%s is invalid", DUMP(frame));
    }
}

}  // namespace Shared

}  // namespace FA
