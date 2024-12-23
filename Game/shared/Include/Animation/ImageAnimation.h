/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "ImageAnimationIf.h"

#include "Resource/ImageFrame.h"
#include "SequenceIf.h"

namespace FA {

namespace Shared {

class ImageAnimation : public ImageAnimationIf
{
public:
    ImageAnimation(std::shared_ptr<SequenceIf<ImageFrame>> seq);

    virtual void Update(float deltaTime) override;  // delta time; time since previous time to current frame
    virtual void ApplyTo(std::shared_ptr<Graphic::DrawableIf> drawable) const override;
    virtual void RegisterUpdateCB(std::function<void(const ImageAnimationIf &)> updateCB) override;
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Restart() override;
    virtual bool IsCompleted() const override;
    virtual void Center() override;

private:
    std::shared_ptr<SequenceIf<ImageFrame>> seq_;
    bool center_{false};
    bool validSeq_{false};
    std::function<void(const ImageAnimationIf &)> updateCB_{[](const ImageAnimationIf &) {}};
};

}  // namespace Shared

}  // namespace FA
