/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicTransition.h"

namespace FA {

namespace Graphic {

class RectangleShapeIf;

}  // namespace Graphic

namespace Scene {

class FadeTransition : public BasicTransition
{
public:
    FadeTransition(CreateSceneFn nextSceneFn);
    virtual ~FadeTransition();

    virtual void Enter(const Graphic::RenderTextureIf& renderTexture) override;
    virtual void DrawTo(Graphic::RenderTargetIf& renderTarget) const override;
    virtual void Update(float deltaTime) override;
    virtual bool IsFinished() const override { return elapsedTime_ > duration_; }

private:
    float elapsedTime_{0.0f};
    std::shared_ptr<Graphic::RectangleShapeIf> fadeRect_;
    int startAlpha_ = 0;
    int endAlpha_ = 255;
};

}  // namespace Scene

}  // namespace FA
