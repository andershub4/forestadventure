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

class ShootAbility : public BasicAbility
{
public:
    ShootAbility(std::function<void(FaceDirection)> enterFn, std::function<void()> exitFn,
                 std::function<void(const sf::Vector2f&)> updateFn);
    virtual ~ShootAbility();

    static const std::string Type() { return "ShootAbility"; }

    virtual void Exit();

private:
    std::function<void(FaceDirection)> enterFn_;
    std::function<void()> exitFn_;
    std::function<void(const sf::Vector2f&)> updateFn_;
};

}  // namespace Entity

}  // namespace FA
