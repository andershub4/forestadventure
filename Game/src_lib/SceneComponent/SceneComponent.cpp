/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SceneComponent.h"

namespace FA {

SceneComponent::SceneComponent(MessageBus& messageBus)
    : messageBus_(messageBus)
{}

SceneComponent::~SceneComponent() = default;

}  // namespace FA
