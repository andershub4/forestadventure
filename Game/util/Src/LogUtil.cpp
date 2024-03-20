/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LogUtil.h"

#include "Logger.h"

namespace FA {

namespace Util {

void MakeDebugLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str)
{
    logger.MakeDebugLogEntry(fn, str);
}

void MakeInfoLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str)
{
    logger.MakeInfoLogEntry(fn, str);
}

void MakeWarnLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str)
{
    logger.MakeWarnLogEntry(fn, str);
}

void MakeErrorLogEntry(LoggerIf& logger, const std::string& fn, const std::string& str)
{
    logger.MakeErrorLogEntry(fn, str);
}

}  // namespace Util

}  // namespace FA
