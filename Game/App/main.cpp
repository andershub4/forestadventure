/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include <SFML/Config.hpp>

#include "Game/Game.h"
#include "Game/Version.h"
#include "SfmlLog.h"
#include "Util/Logger.h"
#include "Util/Path/PathUtil.h"

int main()
{
    OPEN_LOG(FA::Util::GetExePath() + "\\/log.txt");
    LOG_INFO_ENTER_FUNC();
    LOG_INFO(FA_APP_NAME, " version ", FA_APP_VERSION);
    LOG_INFO("SFML version ", SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR);

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
