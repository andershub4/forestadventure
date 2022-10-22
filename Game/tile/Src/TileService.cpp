/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileService.h"

namespace FA {

namespace Tile {

/*
 * Class implementation in header file.
 * This is required since the class is template class.
 * It is a template class to be able to handle dependency injection.
 * Dependency injection with templates is needed to be able to handle testing.
 * Dependency injection with polymorphic was not suitable in this case.
 * Can not derive easily from 3rd party parser class.
 */

}  // namespace Tile

}  // namespace FA
