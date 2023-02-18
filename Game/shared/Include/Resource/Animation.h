/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Frame.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class Animation
{
public:
    Animation() = default;
    Animation(const std::vector<Frame>& frames, unsigned int defaultFrame, float switchTime);

    void Update(float deltaTime);  // delta time; time since previous time to current frame
    void ApplyTo(sf::Sprite& sprite) const;
    void Start();
    void Stop();
    bool IsCompleted() const;
    bool IsValid() const;

private:
    bool isStopped_ = true;
    float time_{};        // time since we last switched frame
    float switchTime_{};  // time before to switch to next frame
    unsigned int iFrame_{};
    std::vector<Frame> frames_;
    unsigned int nFrames_{};
    unsigned int defaultIndex_{};
    bool isCompleted_ = false;
    bool isValid_ = false;
};

}  // namespace Shared

}  // namespace FA
