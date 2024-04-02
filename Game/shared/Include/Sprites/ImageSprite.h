/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "BasicCoolSprite.h"
#include "ImageSpriteIf.h"

#include "Resource/Frame.h"

namespace FA {

namespace Shared {

class ImageSprite : public BasicCoolSprite<ImageSpriteIf>
{
public:
    ImageSprite(std::shared_ptr<Graphic::SpriteIf> sprite, const Frame &frame);

    virtual void Update(float deltaTime) override {}
};

}  // namespace Shared

}  // namespace FA
