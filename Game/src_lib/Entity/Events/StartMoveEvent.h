/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

#include "Enum/MoveDirection.h"
#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

struct StartMoveEvent : public BasicEvent
{
    StartMoveEvent(MoveDirection moveDirection, FaceDirection faceDirection)
        : moveDirection_(moveDirection)
        , faceDirection_(faceDirection)
    {}

    virtual EventType GetEventType() const { return EventType::StartMove; }

    MoveDirection moveDirection_ = MoveDirection::None;
    FaceDirection faceDirection_ = FaceDirection::Undefined;
};

}  // namespace Entity

}  // namespace FA
