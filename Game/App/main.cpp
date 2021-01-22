/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <iostream>

#include "Game/Game.h"
#include "Utils/Logger.h"
#include "SfmlLog.h"

int main()
{
    LOG_INFO_ENTER_FUNC();

    try {
        FA::SfmlLog sfmlLog;
        sfmlLog.Init();
        FA::Game game;
        game.GameLoop();
    }
    catch (const std::exception& e) {
        LOG_ERROR("Exception catched: ", e.what());
        return EXIT_FAILURE;
    }

    LOG_INFO_EXIT_FUNC();
    return EXIT_SUCCESS;
}
