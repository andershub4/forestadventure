/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "Message/Message.h"

namespace FA {

namespace Shared {

class IsKeyPressedMessage : public Message
{
public:
    IsKeyPressedMessage(sf::Keyboard::Key key);

    virtual MessageType GetMessageType() const override { return MessageType::IsKeyPressed; }
    virtual std::string Name() const override { return "IsKeyPressedMessage"; }

    sf::Keyboard::Key GetKey() const { return key_; }

private:
    sf::Keyboard::Key key_ = sf::Keyboard::Key::Unknown;
};

}  // namespace Shared

}  // namespace FA
