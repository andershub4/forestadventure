/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicTransition.h"

#include "Scenes/BasicScene.h"

namespace FA {

namespace Scene {

BasicTransition::BasicTransition(float duration, CreateSceneFn nextSceneFn)
    : duration_(duration)
    , nextSceneFn_(nextSceneFn)
{}

BasicTransition::~BasicTransition() = default;

std::unique_ptr<BasicScene> BasicTransition::CreateNextScene(Shared::MessageBus &messageBus,
                                                             Shared::TextureManager &textureManager) const
{
    return nextSceneFn_(messageBus, textureManager);
}

}  // namespace Scene

}  // namespace FA
