/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <limits>

namespace FA {

namespace Entity {

using EntityId = int;
const EntityId InvalidEntityId = std::numeric_limits<int>::max();

}  // namespace Entity

}  // namespace FA
