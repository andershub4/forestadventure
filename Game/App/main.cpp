/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <SFML/Config.hpp>

#include "Folder.h"
#include "Game/Game.h"
#include "Logging.h"
#include "SfmlLog.h"
#include "Version.h"

int main()
{
    LOG_INFO_ENTER_FUNC();
    LOG_INFO("%s version %s", FA_APP_NAME, FA_APP_VERSION);
    LOG_INFO("SFML version %u.%u.%u", SFML_VERSION_MAJOR, SFML_VERSION_MINOR, SFML_VERSION_PATCH);

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
