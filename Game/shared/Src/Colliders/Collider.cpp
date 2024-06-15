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

Collider::Collider(std::shared_ptr<SequenceIf<sf::FloatRect>> seq)
    : seq_(seq)
{}

void Collider::Update(float deltaTime)
{
    seq_->Update(deltaTime);
}

void Collider::ApplyTo(Graphic::RectangleShapeIf& rectShape, bool center) const
{
    auto rect = seq_->GetCurrent();
    auto size = sf::Vector2f(rect.width, rect.height);
    if (size != sf::Vector2f{}) {
        rectShape.setSize(size);
        if (center) {
            rectShape.setOrigin(rectShape.getLocalBounds().width / 2, rectShape.getLocalBounds().height / 2);
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

void Collider::AddRect(const sf::IntRect& rect)
{
    bool isValid = rect != sf::IntRect{};

    if (isValid) {
        seq_->Add(static_cast<sf::FloatRect>(rect));
    }
    else {
        LOG_WARN("%s is invalid", DUMP(rect));
    }
}

}  // namespace Shared

}  // namespace FA
