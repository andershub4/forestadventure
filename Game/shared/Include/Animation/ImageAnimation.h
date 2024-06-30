/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

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
    virtual void ApplyTo(Graphic::SpriteIf &sprite, bool center) const override;
    virtual void Start() override;
    virtual void Stop() override;
    virtual bool IsCompleted() const override;

private:
    std::shared_ptr<SequenceIf<ImageFrame>> seq_;
};

}  // namespace Shared

}  // namespace FA
