/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>

#include "BasicAbility.h"

#include "Enum/FaceDirection.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class DieAbility : public BasicAbility
{
public:
    DieAbility(std::function<void()> updateFn);
    virtual ~DieAbility();

    virtual void Update(float deltaTime) override;

private:
    std::function<void()> updateFn_;
};

}  // namespace Entity

}  // namespace FA
