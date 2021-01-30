/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameTransitionNone.h"

namespace FA {

GameTransitionNone::GameTransitionNone(CreateSceneFn nextSceneFn)
    : GameTransition(nextSceneFn)
{}

GameTransitionNone::~GameTransitionNone() = default;

void GameTransitionNone::DrawTo(sf::RenderTarget& renderTarget)
{}

void GameTransitionNone::DrawTo(SceneComponent& sceneComponent)
{}

void GameTransitionNone::Update(float deltaTime)
{}

}  // namespace FA
