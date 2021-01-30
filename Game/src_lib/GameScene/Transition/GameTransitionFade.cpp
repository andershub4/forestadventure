/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameTransitionFade.h"

#include "Constant/Screen.h"
#include "SceneComponent/SceneComponent.h"

namespace FA {

GameTransitionFade::GameTransitionFade(CreateSceneFn nextSceneFn)
    : GameTransition(nextSceneFn)
    , fade_(sf::Vector2f(constant::Screen::width_f, constant::Screen::height_f), 1.0f)
{}

GameTransitionFade::~GameTransitionFade() = default;

void GameTransitionFade::DrawTo(sf::RenderTarget& renderTarget)
{
    fade_.DrawTo(renderTarget);
}

void GameTransitionFade::DrawTo(SceneComponent& sceneComponent)
{
    sceneComponent.Draw(fade_);
}

void GameTransitionFade::Update(float deltaTime)
{
    fade_.Update(deltaTime);
}

bool GameTransitionFade::IsFinished() const
{
    return fade_.IsFinished();
}

}  // namespace FA
