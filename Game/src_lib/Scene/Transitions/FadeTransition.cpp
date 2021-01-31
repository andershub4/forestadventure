/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "FadeTransition.h"

#include "Constant/Screen.h"
#include "Scene/Components/BasicComponent.h"

namespace FA {

namespace Scene {

FadeTransition::FadeTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(nextSceneFn)
    , fade_(sf::Vector2f(constant::Screen::width_f, constant::Screen::height_f), 1.0f)
{}

FadeTransition::~FadeTransition() = default;

void FadeTransition::DrawTo(sf::RenderTarget& renderTarget)
{
    fade_.DrawTo(renderTarget);
}

void FadeTransition::DrawTo(BasicComponent& component)
{
    component.Draw(fade_);
}

void FadeTransition::Update(float deltaTime)
{
    fade_.Update(deltaTime);
}

bool FadeTransition::IsFinished() const
{
    return fade_.IsFinished();
}

}  // namespace Scene

}  // namespace FA
