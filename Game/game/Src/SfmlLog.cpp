/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SfmlLog.h"

#include <SFML/Config.hpp>
#include <SFML/System/Err.hpp>

#include "Folder.h"
#include "Logging.h"

namespace FA {

void SfmlLog::Init()
{
    const std::string path = GetLogPath() + '/' + "sfml-log.txt";
    sfmlLogStream_.open(path);

    if (sfmlLogStream_.is_open()) {
        LOG_INFO("Redirecting sfml log entries to %s", DUMP(path));
        sfmlLogStream_ << "SFML version " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << std::endl;
        sf::err().rdbuf(sfmlLogStream_.rdbuf());
    }
}

}  // namespace FA
