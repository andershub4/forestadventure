/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicSprite.h"
#include "Resource/Animation.h"

namespace FA {

namespace Entity {

class AnimationSprite : public BasicSprite
{
public:
    AnimationSprite(std::function<std::string()> getKey,
                    const std::unordered_map<std::string, Shared::Animation> &animations,
                    std::function<void(const Shared::Animation &)>, bool center = true);
    AnimationSprite(std::function<std::string()> getKey,
                    const std::unordered_map<std::string, Shared::Animation> &animations, bool center = true);
    virtual ~AnimationSprite();

    virtual void Enter() override;
    virtual void Update(float deltaTime) override;

private:
    std::unordered_map<std::string, Shared::Animation> map_;
    Shared::Animation currentAnimation_;
    std::function<std::string()> getKey_;
    std::function<void(const Shared::Animation &)> updateFn_;
    bool center_{};
};

}  // namespace Entity

}  // namespace FA
