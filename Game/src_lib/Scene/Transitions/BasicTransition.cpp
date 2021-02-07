/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicTransition.h"

#include "Scene/Scenes/BasicScene.h"

namespace FA {

namespace Scene {

BasicTransition::BasicTransition(float seconds, CreateSceneFn nextSceneFn)
    : targetTime_(sf::seconds(seconds))
    , nextSceneFn_(nextSceneFn)
    , seconds_(seconds)
{}

BasicTransition::~BasicTransition() = default;

std::unique_ptr<BasicScene> BasicTransition::CreateNextScene(MessageBus &messageBus,
                                                             TextureManager &textureManager) const
{
    return nextSceneFn_(messageBus, textureManager);
}

bool BasicTransition::IsFinished() const
{
    return clock_.getElapsedTime() >= targetTime_;
}

}  // namespace Scene

}  // namespace FA
