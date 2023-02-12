/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <fstream>

namespace FA {

class SfmlLog
{
public:
    void Init();

private:
    std::ofstream sfmlLogStream_;
};

}  // namespace FA
