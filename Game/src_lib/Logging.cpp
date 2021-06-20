/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logging.h"

namespace FA {

LogLib::Logger& MainLog()
{
    static LogLib::Logger mainLog;
    return mainLog;
}

}  // namespace FA
