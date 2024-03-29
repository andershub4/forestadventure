/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Message/Message.h"

namespace FA {

namespace Shared {

class EntityInitializedMessage : public Message
{
public:
    virtual MessageType GetMessageType() const override { return MessageType::EntityInitialized; }
    virtual std::string Name() const override { return "EntityInitialized"; }
};

}  // namespace Shared

}  // namespace FA
