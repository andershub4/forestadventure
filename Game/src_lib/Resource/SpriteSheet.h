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

class SpriteSheet
{
public:
    struct FrameSeq
    {
        const sf::Texture* texture_ = nullptr;
        unsigned int defaultIndex_ = 0;
        std::vector<sf::IntRect> rects_;
        bool isValid_ = false;
    };

    struct Frame
    {
        const sf::Texture* texture_ = nullptr;
        sf::IntRect rect_;
        bool isValid_ = false;
    };

    SpriteSheet() = default;
    SpriteSheet(const sf::Texture* texture, const sf::Vector2u& rectCount);

    static std::vector<sf::IntRect> MirrorX(const std::vector<sf::IntRect>& rects);

    bool IsValid() const { return isValid_; }
    FrameSeq Scan(const sf::Vector2u& uvCoord, unsigned int nRects, unsigned int defaultIndex) const;
    Frame At(const sf::Vector2u& uvCoord) const;

private:
    const sf::Texture* texture_;
    sf::Vector2u rectCount_;
    bool isValid_ = false;

private:
    sf::Vector2u CalcRectSize() const;
    std::vector<sf::IntRect> GenerateRects(const sf::Vector2u& uvCoord, unsigned int nRects) const;
};

}  // namespace FA
