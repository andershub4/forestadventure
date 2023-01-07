/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Message/Message.h"

#include <SFML/Window/Keyboard.hpp>

namespace FA {

namespace Shared {

class KeyReleasedMessage : public Message
{
public:
    KeyReleasedMessage(sf::Keyboard::Key key);

    virtual MessageType GetMessageType() const override { return MessageType::KeyReleased; }
    virtual std::string Name() const override { return "KeyReleased"; }

    sf::Keyboard::Key GetKey() const { return key_; }

private:
    sf::Keyboard::Key key_ = sf::Keyboard::Key::Unknown;
};

}  // namespace Shared

}  // namespace FA
