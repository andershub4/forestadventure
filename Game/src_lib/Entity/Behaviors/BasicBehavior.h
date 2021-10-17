/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Entity/BasicProperty.h"

namespace FA {

namespace Entity {

class BasicBehavior : public BasicProperty
{
public:
    BasicBehavior(EntityService* owner);
    virtual ~BasicBehavior();

    virtual void Awake() {}
};

}  // namespace Entity

}  // namespace FA
