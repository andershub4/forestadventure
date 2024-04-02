/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "AnimationSpriteIf.h"
#include "BasicCoolSprite.h"

#include "Resource/Frame.h"

namespace FA {

namespace Shared {

class AnimationSprite : public BasicCoolSprite<AnimationSpriteIf>
{
public:
    AnimationSprite(std::shared_ptr<Graphic::SpriteIf> sprite, float switchTime);

    virtual void Update(float deltaTime) override;  // delta time; time since previous time to current frame

    virtual void Start() override;
    virtual void Stop() override;
    virtual bool IsCompleted() const override;
    virtual void AddFrame(const Frame &frame) override;

private:
    bool isStopped_ = true;
    float switchTime_{};  // time before to switch to next frame
    float time_{};        // time since we last switched frame
    unsigned int iFrame_{};
    std::vector<Frame> frames_;
    unsigned int nFrames_{};
    bool isCompleted_ = false;
    bool isValid_ = false;
};

}  // namespace Shared

}  // namespace FA
