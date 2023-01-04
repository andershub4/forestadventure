/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "DieAbility.h"

namespace FA {

namespace Entity {

DieAbility::DieAbility(std::function<void()> updateFn)
    : updateFn_(updateFn)
{}

DieAbility::~DieAbility() = default;

void DieAbility::Update(float deltaTime)
{
    updateFn_();
}

}  // namespace Entity

}  // namespace FA
