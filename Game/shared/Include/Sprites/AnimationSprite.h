/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "BasicSprite.h"

#include "Resource/Frame.h"

namespace FA {

namespace Shared {

class AnimationSprite : public BasicSprite
{
public:
    AnimationSprite(std::shared_ptr<Graphic::ISprite> sprite, unsigned int defaultFrame, float switchTime);

    virtual void Update(float deltaTime) override;  // delta time; time since previous time to current frame

    void Start();
    void Stop();
    bool IsCompleted() const;
    void AddFrame(const Frame &frame);

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
