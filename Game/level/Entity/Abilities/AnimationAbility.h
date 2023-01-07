/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicAbility.h"

#include "Fwd/SfmlFwd.h"
#include "Resource/Animation.h"

namespace FA {

namespace Entity {

class AnimationAbility : public BasicAbility
{
public:
    AnimationAbility(std::function<std::string()> getKey, std::function<void(const Shared::Animation &)>);
    virtual ~AnimationAbility();

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;
    virtual void Update(float deltaTime) override;

    void RegisterAnimation(const std::string &name, const Shared::Animation &animation);
    bool AnimationIsCompleted() const;

private:
    std::unordered_map<std::string, Shared::Animation> map_;
    Shared::Animation currentAnimation_;
    std::function<std::string()> getKey_;
    std::function<void(const Shared::Animation &)> updateFn_;
};

}  // namespace Entity

}  // namespace FA
