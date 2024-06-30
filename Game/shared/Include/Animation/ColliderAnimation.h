/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "ColliderAnimationIf.h"

#include "Resource/ColliderFrame.h"
#include "SequenceIf.h"

namespace FA {

namespace Shared {

class ColliderAnimation : public ColliderAnimationIf
{
public:
    ColliderAnimation(std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq);

    virtual void Update(float deltaTime) override;  // delta time; time since previous time to current frame
    virtual void ApplyTo(Graphic::RectangleShapeIf &rectShape, bool center) const override;
    virtual void Start() override;
    virtual void Stop() override;
    virtual bool IsCompleted() const override;

private:
    std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq_;
};

}  // namespace Shared

}  // namespace FA