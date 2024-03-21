/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

namespace FA {

namespace Entity {

struct BasicEvent;

class AbilityIf
{
public:
    virtual ~AbilityIf() = default;

    virtual void Enter(std::shared_ptr<BasicEvent> event) {}
    virtual void Exit() {}
    virtual void Update(float deltaTime) {}
};

}  // namespace Entity

}  // namespace FA
