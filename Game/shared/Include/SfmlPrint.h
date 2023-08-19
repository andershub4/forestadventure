/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

#include <SFML/System/Vector2.hpp>

#include "Print.h"

namespace FA {

namespace Shared {
    
template <class T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& p)
{
    os << OUT2("x", p.x) << DELIM << OUT2("y", p.y);

    return os;
}

}  // namespace Shared

}  // namespace FA
