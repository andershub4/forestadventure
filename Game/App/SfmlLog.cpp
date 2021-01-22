/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SfmlLog.h"

#include <SFML/Config.hpp>
#include <SFML/System/Err.hpp>

#include "Utils/Logger.h"
#include "Utils/Path.h"

namespace FA {

void SfmlLog::Init()
{
    const std::string sfmlLog = "sfml-log.txt";
    sfmlLogStream_.open(GetExePath() + "\\/" + sfmlLog);

    if (sfmlLogStream_.is_open()) {
        LOG_INFO("Redirecting sfml log entries to ", sfmlLog);
        sfmlLogStream_ << "SFML version " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << std::endl;
        sf::err().rdbuf(sfmlLogStream_.rdbuf());
    }
}

}  // namespace FA
