/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Entity/BasicProperty.h"

namespace FA {

namespace Entity {

class BasicAttribute : public BasicProperty
{
public:
    BasicAttribute(EntityService* owner);
    virtual ~BasicAttribute();

    virtual void Awake() {}
};

}  // namespace Entity

}  // namespace FA
