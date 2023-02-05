/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ShootAbility.h"

namespace FA {

namespace Entity {

ShootAbility::ShootAbility(std::function<void(FaceDirection)> enterFn, std::function<void()> exitFn,
                           std::function<void(const sf::Vector2f&)> updateFn)
    : enterFn_(enterFn)
    , exitFn_(exitFn)
    , updateFn_(updateFn)
{}

ShootAbility::~ShootAbility() = default;

void ShootAbility::Exit()
{
    exitFn_();
}

}  // namespace Entity

}  // namespace FA
