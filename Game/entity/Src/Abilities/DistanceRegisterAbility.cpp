/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "DistanceRegisterAbility.h"

namespace FA {

namespace Entity {

DistanceRegisterAbility::DistanceRegisterAbility(float velocity, std::function<void(float)> updateFn)
    : updateFn_(updateFn)
    , velocity_(velocity)
{}

DistanceRegisterAbility::~DistanceRegisterAbility() = default;

void DistanceRegisterAbility::Update(float deltaTime)
{
    distance_ += deltaTime * velocity_;
    updateFn_(distance_);
}

void DistanceRegisterAbility::Exit()
{
    distance_ = 0.0f;
}

}  // namespace Entity

}  // namespace FA
