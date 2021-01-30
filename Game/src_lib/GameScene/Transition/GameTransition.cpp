/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "GameTransition.h"

#include "GameScene/Scene/GameScene.h"

namespace FA {

GameTransition::GameTransition(CreateSceneFn nextSceneFn)
    : nextSceneFn_(nextSceneFn)
{}

GameTransition::~GameTransition() = default;

std::unique_ptr<GameScene> GameTransition::CreateNextScene(MessageBus &messageBus, TextureManager &textureManager) const
{
    return nextSceneFn_(messageBus, textureManager);
}

}  // namespace FA
