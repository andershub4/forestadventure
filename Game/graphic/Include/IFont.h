/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Graphic {

class IFont
{
public:
    virtual ~IFont() = default;
    virtual bool loadFromFile(const std::string &filename) = 0;
};

}  // namespace Graphic

}  // namespace FA
