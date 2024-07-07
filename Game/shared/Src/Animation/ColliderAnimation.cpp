/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation/ColliderAnimation.h"

#include <SFML/Graphics/Rect.hpp>
#include "SFML/Graphics/Color.hpp"

#include "RectangleShapeIf.h"
#include "RenderTargetIf.h"

namespace FA {

namespace Shared {

ColliderAnimation::ColliderAnimation(std::shared_ptr<Graphic::RectangleShapeIf> rectShape,
                                     std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq)
    : rectShape_(rectShape)
    , seq_(seq)
{
    validSeq_ = !seq->IsEmpty();
    rectShape_->setFillColor(sf::Color::Transparent);
    rectShape_->setOutlineColor(sf::Color::Red);
    rectShape_->setOutlineThickness(1.0f);
}

void ColliderAnimation::Update(float deltaTime)
{
    if (validSeq_) {
        seq_->Update(deltaTime);
        auto frame = seq_->GetCurrent();
        rectShape_->setSize(frame.size_);
        if (center_) {
            rectShape_->setOrigin(frame.center_.x, frame.center_.y);
        }
    }
}

void ColliderAnimation::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    renderTarget.draw(*rectShape_);
}

bool ColliderAnimation::Intersects(const ColliderAnimationIf &other) const
{
    auto otherImpl = static_cast<const ColliderAnimation &>(other);
    return rectShape_->getGlobalBounds().intersects(otherImpl.rectShape_->getGlobalBounds());
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

void ColliderAnimation::Center()
{
    center_ = true;
}

void ColliderAnimation::SetPosition(const sf::Vector2f &position)
{
    rectShape_->setPosition(position);
}

void ColliderAnimation::SetRotation(float angle)
{
    rectShape_->setRotation(angle);
}

}  // namespace Shared

}  // namespace FA
