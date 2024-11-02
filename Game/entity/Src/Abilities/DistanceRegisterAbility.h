/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>

#include "AbilityIf.h"

namespace FA {

namespace Entity {

class DistanceRegisterAbility : public AbilityIf
{
public:
    DistanceRegisterAbility(float velocity, std::function<void(float)> updateFn);
    virtual ~DistanceRegisterAbility();

    virtual void Update(float deltaTime) override;
    virtual void Exit() override;

private:
    std::function<void(float)> updateFn_;
    float velocity_{};
    float distance_{};
};

}  // namespace Entity

}  // namespace FA
