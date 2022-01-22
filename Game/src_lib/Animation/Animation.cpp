/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation.h"

#include <SFML/Graphics/Sprite.hpp>

namespace FA {

Animation::Animation(const sf::Texture* texture, const std::vector<sf::IntRect>& frames, unsigned int defaultFrame,
                     float switchTime)
    : texture_(texture)
    , frames_(frames)
    , switchTime_(switchTime)
    , time_(0.0)
    , defaultFrame_(defaultFrame)
    , iFrame_(defaultFrame)
    , isValid_(true)
{
    nFrames_ = frames.size();
}

void Animation::ApplyTo(sf::Sprite& sprite)
{
    sprite.setTexture(*texture_);
    sprite.setTextureRect(frames_[iFrame_]);
}

void Animation::Update(float deltaTime)
{
    if (!isStopped_ && nFrames_ > 1) {
        time_ += deltaTime;

        while (time_ >= switchTime_) {
            time_ -= switchTime_;
            ++iFrame_ %= nFrames_;
            isCompleted_ = (iFrame_ == 0);
        }
    }
}

void Animation::Start()
{
    isStopped_ = false;
}

void Animation::Stop()
{
    isStopped_ = true;
    iFrame_ = defaultFrame_;
}

bool Animation::IsCompleted() const
{
    return isCompleted_;
}

bool Animation::IsValid() const
{
    return isValid_;
}

}  // namespace FA
