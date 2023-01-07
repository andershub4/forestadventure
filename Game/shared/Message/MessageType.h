/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Shared {

enum class MessageType {
    Undefined,
    KeyPressed,
    KeyReleased,
    IsKeyPressed,
    CloseWindow,
    EntityCreated,
    EntityDestroyed,
    GameOver
};

}  // namespace Shared

}  // namespace FA
