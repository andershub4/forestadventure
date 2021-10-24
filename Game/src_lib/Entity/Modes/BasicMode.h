/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Entity/BasicProperty.h"

#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class BasicMode : public BasicProperty
{
public:
    BasicMode(EntityService* owner);
    virtual ~BasicMode();

    virtual FrameType GetFrameType() const = 0;

    virtual void Awake() {}
    virtual void Init() {}
};

}  // namespace Entity

}  // namespace FA
