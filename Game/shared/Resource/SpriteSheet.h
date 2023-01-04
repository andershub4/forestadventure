/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

struct Frame;

class SpriteSheet
{
public:
    SpriteSheet() = default;
    SpriteSheet(const sf::Texture* texture, const sf::Vector2u& rectCount);

    static std::vector<Frame> MirrorX(const std::vector<Frame>& frames);

    bool IsValid() const { return isValid_; }
    std::vector<Frame> Scan(const sf::Vector2u& uvCoord, unsigned int nRects) const;
    Frame At(const sf::Vector2u& uvCoord) const;

private:
    const sf::Texture* texture_ = nullptr;
    sf::Vector2u rectCount_;
    bool isValid_ = false;

private:
    sf::Vector2u CalcRectSize() const;
    std::vector<Frame> GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nRects) const;
};

}  // namespace FA
