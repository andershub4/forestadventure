/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IsKeyPressedMessage.h"

namespace FA {

namespace Shared {

IsKeyPressedMessage::IsKeyPressedMessage(sf::Keyboard::Key key)
    : key_(key)
{}

}  // namespace Shared

}  // namespace FA
