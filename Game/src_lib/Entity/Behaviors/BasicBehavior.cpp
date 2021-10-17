/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicBehavior.h"

namespace FA {

namespace Entity {

BasicBehavior::BasicBehavior(EntityService *owner)
    : BasicProperty(owner)
{}

BasicBehavior::~BasicBehavior() = default;

}  // namespace Entity

}  // namespace FA
