/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "ColliderIf.h"

#include "SequenceIf.h"

namespace FA {

namespace Shared {

class Collider : public ColliderIf
{
public:
    Collider(std::shared_ptr<SequenceIf<sf::FloatRect>> seq);

    virtual void Update(float deltaTime) override;  // delta time; time since previous time to current frame
    virtual void ApplyTo(Graphic::RectangleShapeIf &rectShape, bool center) const override;
    virtual void Start() override;
    virtual void Stop() override;
    virtual bool IsCompleted() const override;
    virtual void AddRect(const sf::IntRect &rect) override;

private:
    std::shared_ptr<SequenceIf<sf::FloatRect>> seq_;
};

}  // namespace Shared

}  // namespace FA
