/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

namespace FA {

namespace Util {

class BasicLogger
{
public:
    virtual ~BasicLogger() = default;

    virtual void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole) = 0;
    virtual void CloseLog() = 0;
    virtual void MakeDebugLogEntry(const std::string& fn, const std::string& str) = 0;
    virtual void MakeInfoLogEntry(const std::string& fn, const std::string& str) = 0;
    virtual void MakeWarnLogEntry(const std::string& fn, const std::string& str) = 0;
    virtual void MakeErrorLogEntry(const std::string& fn, const std::string& str) = 0;
};

}  // namespace Util

}  // namespace FA
