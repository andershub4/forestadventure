/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Animation.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace FA {

Animation::Animation(sf::Sprite* sprite, const sf::Texture* texture, const std::vector<sf::IntRect>& frames,
                     unsigned int defaultFrame, float switchTime)
    : sprite_(sprite)
    , texture_(texture)
    , frames_(frames)
    , switchTime_(switchTime)
    , time_(0.0)
    , defaultFrame_(defaultFrame)
    , iFrame_(defaultFrame)
{
    nFrames_ = frames.size();
    sprite_->setTexture(*texture_);
    if (defaultFrame_ < nFrames_) sprite_->setTextureRect(frames_.at(defaultFrame_));
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

        sprite_->setTextureRect(frames_[iFrame_]);
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

}  // namespace FA
