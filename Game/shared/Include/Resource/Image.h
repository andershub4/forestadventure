/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Frame.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class Image
{
public:
    Image() = default;
    Image(const Frame& frame);

    void Update(float deltaTime);
    void ApplyTo(sf::Sprite& sprite) const;
    bool IsValid() const;

private:
    Frame frame_;
    bool isValid_ = false;
};

}  // namespace Shared

}  // namespace FA
