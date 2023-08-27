/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "Frame.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class Animation
{
public:
    Animation() = default;
    Animation(std::shared_ptr<sf::Sprite> sprite, unsigned int defaultFrame, float switchTime);

    void Update(float deltaTime);  // delta time; time since previous time to current frame
    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void DrawTo(sf::RenderTarget &renderTarget);
    void Center();
    void Start();
    void Stop();
    bool IsCompleted() const;
    bool IsValid() const;
    void AddFrame(const Frame &frame);

private:
    std::shared_ptr<sf::Sprite> sprite_;
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
