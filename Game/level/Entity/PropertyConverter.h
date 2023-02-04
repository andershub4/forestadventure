/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

template <class T>
T ToValue(const std::string &value)
{
    return T();
}

template <>
FaceDirection ToValue(const std::string &valueStr);

}  // namespace Entity

}  // namespace FA
