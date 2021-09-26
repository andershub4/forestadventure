/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicComponent.h"

namespace FA {

namespace Entity {

BasicComponent::BasicComponent(ComponentHandler *owner)
    : owner_(owner)
{}

BasicComponent::~BasicComponent() = default;

}  // namespace Entity

}  // namespace FA
