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
    };

    SpriteSheet(const std::string& name, const sf::Texture* texture, const sf::Vector2u& frameCount);

    FrameData Scan(const sf::Vector2u& uvCoord, unsigned int nFrames, unsigned int defaultFrame) const;

private:
    const sf::Texture* texture_;
    sf::Vector2u frameCount_;

private:
    unsigned int CalcFrameSize() const;
    std::vector<sf::IntRect> GenerateFrames(const sf::Vector2u& uvCoord, unsigned int nFrames,
                                            unsigned int frameSize) const;
};

}  // namespace FA
