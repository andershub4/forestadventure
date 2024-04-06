/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicCoolSprite.h"
#include "ImageSpriteIf.h"

#include "Resource/Frame.h"

namespace FA {

namespace Shared {

class ImageSprite : public BasicCoolSprite<ImageSpriteIf>
{
public:
    ImageSprite(const Frame &frame);

    virtual void ApplyTo(Graphic::SpriteIf &sprite) const override;

private:
    Frame frame_{};
    bool isValid_{false};
};

}  // namespace Shared

}  // namespace FA
