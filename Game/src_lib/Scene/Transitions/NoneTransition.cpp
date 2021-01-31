/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "NoneTransition.h"

namespace FA {

namespace Scene {

NoneTransition::NoneTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(nextSceneFn)
{}

NoneTransition::~NoneTransition() = default;

void NoneTransition::DrawTo(sf::RenderTarget& renderTarget)
{}

void NoneTransition::DrawTo(BasicComponent& component)
{}

void NoneTransition::Update(float deltaTime)
{}

}  // namespace Scene

}  // namespace FA
