/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicSprite.h"

#include <memory>

#include "Resource/Frame.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class ImageSprite : public BasicSprite
{
public:
    ImageSprite(std::shared_ptr<sf::Sprite> sprite, const Frame &frame);
    ImageSprite() = default;

    virtual void Update(float deltaTime) override;

private:
    Frame frame_;
};

}  // namespace Shared

}  // namespace FA
