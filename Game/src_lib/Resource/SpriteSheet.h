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
    struct FrameData
    {
        const sf::Texture* texture_ = nullptr;
        unsigned int defaultFrame_ = 0;
        std::vector<sf::IntRect> frames_;
        bool isValid_ = false;
    };

    SpriteSheet() = default;
    SpriteSheet(const sf::Texture* texture, const sf::Vector2u& frameCount);

    static std::vector<sf::IntRect> MirrorX(const std::vector<sf::IntRect>& frames);

    bool IsValid() const { return isValid_; }
    FrameData Scan(const sf::Vector2u& uvCoord, unsigned int nFrames, unsigned int defaultFrame) const;

private:
    const sf::Texture* texture_;
    sf::Vector2u frameCount_;
    bool isValid_ = false;

private:
    sf::Vector2u CalcFrameSize() const;
    std::vector<sf::IntRect> GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nFrames,
                                            const sf::Vector2u& frameSize) const;
};

}  // namespace FA
