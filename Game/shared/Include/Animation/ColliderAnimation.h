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

namespace Graphic {

class RectangleShapeIf;

}  // namespace Graphic

namespace Shared {

class ColliderAnimation : public ColliderAnimationIf
{
public:
    ColliderAnimation(std::shared_ptr<Graphic::RectangleShapeIf> rectShape,
                      std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq);

    virtual void Update(float deltaTime) override;  // delta time; time since previous time to current frame
    virtual void DrawTo(Graphic::RenderTargetIf &renderTarget) const override;
    virtual bool Intersects(const ColliderAnimationIf &other) const override;
    virtual void RegisterUpdateCB(std::function<void(const ColliderAnimationIf &)> updateCB) override;
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Restart() override;
    virtual bool IsCompleted() const override;
    virtual void Center() override;
    virtual void SetPosition(const sf::Vector2f &position) override;
    virtual void SetRotation(float angle) override;

private:
    std::shared_ptr<Graphic::RectangleShapeIf> rectShape_;
    std::shared_ptr<SequenceIf<Shared::ColliderFrame>> seq_;
    bool center_{false};
    bool validSeq_{false};
    std::function<void(const ColliderAnimationIf &)> updateCB_{[](const ColliderAnimationIf &) {}};
};

}  // namespace Shared

}  // namespace FA
