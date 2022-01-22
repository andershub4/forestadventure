/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class Image
{
public:
    Image() = default;
    Image(const sf::Texture* texture, const sf::IntRect& frame, float rotation);

    void Update(float deltaTime);
    void ApplyTo(sf::Sprite& sprite);
    bool IsValid() const;

private:
    const sf::Texture* texture_ = nullptr;
    sf::IntRect frame_;
    float rotation_{};
    bool isValid_ = false;
};

}  // namespace FA
