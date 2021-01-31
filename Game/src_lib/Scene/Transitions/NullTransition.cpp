/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "NullTransition.h"

namespace FA {

namespace Scene {

NullTransition::NullTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(nextSceneFn)
{}

NullTransition::~NullTransition() = default;

void NullTransition::DrawTo(sf::RenderTarget& renderTarget)
{}

void NullTransition::DrawTo(BasicComponent& component)
{}

void NullTransition::Update(float deltaTime)
{}

}  // namespace Scene

}  // namespace FA
