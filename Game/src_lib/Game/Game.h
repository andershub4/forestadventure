/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

class Game
{
public:
    int Run();

private:
    void GameLoop();
};

}  // namespace FA
