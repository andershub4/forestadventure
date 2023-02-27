/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "AnimationTable.h"
#include "BasicSprite.h"
#include "Resource/Animation.h"

namespace FA {

namespace Entity {

class AnimationSprite : public BasicSprite
{
public:
    AnimationSprite(const AnimationTable &table, std::function<void(const Shared::Animation &)>, bool center = true);
    AnimationSprite(const AnimationTable &table, bool center = true);
    virtual ~AnimationSprite();

    virtual void Enter() override;
    virtual void Update(float deltaTime) override;

private:
    AnimationTable table_;
    Shared::Animation currentAnimation_;
    std::function<void(const Shared::Animation &)> updateFn_;
    bool center_{};
};

}  // namespace Entity

}  // namespace FA
