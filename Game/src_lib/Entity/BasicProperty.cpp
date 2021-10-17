/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicProperty.h"

namespace FA {

namespace Entity {

BasicProperty::BasicProperty(EntityService *owner)
    : owner_(owner)
{}

BasicProperty::~BasicProperty() = default;

}  // namespace Entity

}  // namespace FA
