/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEvent.h"

#include "Enum/FaceDirection.h"
#include "Enum/MoveDirection.h"

namespace FA {

namespace Entity {

struct StartMoveEvent : public BasicEvent
{
    StartMoveEvent(MoveDirection moveDirection, FaceDirection faceDirection, float rotation)
        : moveDirection_(moveDirection)
        , faceDirection_(faceDirection)
        , rotation_(rotation)
    {}

    virtual EventType GetEventType() const { return EventType::StartMove; }

    MoveDirection moveDirection_ = MoveDirection::None;
    FaceDirection faceDirection_ = FaceDirection::Undefined;
    float rotation_{};
};

}  // namespace Entity

}  // namespace FA
