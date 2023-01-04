/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Message/Message.h"

namespace FA {

class CloseWindowMessage : public Message
{
public:
    virtual MessageType GetMessageType() const override { return MessageType::CloseWindow; }
    virtual std::string Name() const override { return "CloseWindow"; }
};

}  // namespace FA
