/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedMode.h"

namespace FA {

namespace Entity {

UninitializedMode::UninitializedMode(EntityService& entityService, ModeController& modeController)
    : BasicMode(entityService, modeController)
{}

}  // namespace Entity

}  // namespace FA
