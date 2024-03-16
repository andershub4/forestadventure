/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LogUtil.h"

#include "Logger.h"

namespace FA {

void MakeDebugLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str)
{
    logger.MakeDebugLogEntry(fn, str);
}

void MakeInfoLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str)
{
    logger.MakeInfoLogEntry(fn, str);
}

void MakeWarnLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str)
{
    logger.MakeWarnLogEntry(fn, str);
}

void MakeErrorLogEntry(LogLib::BasicLogger& logger, const std::string& fn, const std::string& str)
{
    logger.MakeErrorLogEntry(fn, str);
}

}  // namespace FA
