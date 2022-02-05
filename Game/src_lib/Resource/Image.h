/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Frame.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class Image
{
public:
    Image() = default;
    Image(const Frame& frame, float rotation);

    void Update(float deltaTime);
    void ApplyTo(sf::Sprite& sprite);
    bool IsValid() const;

private:
    Frame frame_;
    float rotation_{};
    bool isValid_ = false;
};

}  // namespace FA
