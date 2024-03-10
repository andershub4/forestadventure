/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "NullTransition.h"

namespace FA {

namespace Scene {

NullTransition::NullTransition(CreateSceneFn nextSceneFn)
    : BasicTransition(0.0, nextSceneFn)
{}

NullTransition::~NullTransition() = default;

}  // namespace Scene

}  // namespace FA
