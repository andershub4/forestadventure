/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <ostream>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Print.h"

/*
It is not optimal to add code to a 3rd party namespace.
However, this is done so ADL will work;
When printing from failing gtest (from testing namespace), the type (eg sf::Vector2<T>)
will be printed by operator <<. By adding this operator to the sf namespace,
the operator will be found thanks to ADL.
An alternative to this solution is add these operator overloading to global namespace.
And in each defintion of operator <<, explicit declare usage of the global operator.

using ::operator<<;
inline std::ostream& operator<<(std::ostream& os, const SheetItem& p)
{
    os << OUT2("id", p.id_) << DELIM << OUT2("position", p.position_);

    return os;
}
*/

namespace sf {

template <class T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& p)
{
    os << OUT2("x", p.x) << DELIM << OUT2("y", p.y);

    return os;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, const sf::Rect<T>& p)
{
    os << OUT2("left", p.left) << DELIM << OUT2("top", p.top) << DELIM << OUT2("width", p.width) << DELIM
       << OUT2("height", p.height);

    return os;
}

}  // namespace sf

namespace FA {

namespace Shared {

}  // namespace Shared

}  // namespace FA
