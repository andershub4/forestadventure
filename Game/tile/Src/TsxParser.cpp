/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TsxParser.h"

namespace FA {

namespace Tile {

/*
 * Class implemenation moved to header tile.
 * This was required since the class became a template class.
 * It became a template class to be able to handle dependency injection.
 * Dependency injection with templates is needed to be able to handle testing.
 * Dependency injection with polymorphic was not suitable in this case.
 * Can not derive easily from 3rd party parser class.
 */

}  // namespace Tile

}  // namespace FA
