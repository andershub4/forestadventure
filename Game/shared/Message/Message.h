/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "MessageType.h"

namespace FA {

namespace Shared {

class Message
{
public:
    Message() = default;
    virtual ~Message();

    virtual MessageType GetMessageType() const = 0;
    virtual std::string Name() const = 0;
};

}  // namespace Shared

}  // namespace FA
