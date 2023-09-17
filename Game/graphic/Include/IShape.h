/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "IDrawable.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class IShape : public IDrawable
{
public:
    virtual ~IShape() = default;
};

}  // namespace Graphic

}  // namespace FA
