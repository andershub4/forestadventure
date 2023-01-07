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

class KeyPressedMessage : public Message
{
public:
    KeyPressedMessage(sf::Keyboard::Key key);

    virtual MessageType GetMessageType() const override { return MessageType::KeyPressed; }
    virtual std::string Name() const override { return "KeyPressed"; }

    sf::Keyboard::Key GetKey() const { return key_; }

private:
    sf::Keyboard::Key key_ = sf::Keyboard::Key::Unknown;
};

}  // namespace Shared

}  // namespace FA
