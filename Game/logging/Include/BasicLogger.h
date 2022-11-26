/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <cstdarg>
#include <string>

namespace LogLib {

class BasicLogger
{
public:
    static std::string ToString(const char* format, ...);

    virtual ~BasicLogger() = default;

    virtual void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole) = 0;
    virtual void CloseLog() = 0;
    virtual void MakeDebugLogEntry(const std::string& fn, const std::string& str) = 0;
    virtual void MakeInfoLogEntry(const std::string& fn, const std::string& str) = 0;
    virtual void MakeWarnLogEntry(const std::string& fn, const std::string& str) = 0;
    virtual void MakeErrorLogEntry(const std::string& fn, const std::string& str) = 0;

protected:
    static constexpr int maxLogEntrySize_{40000};  // arbitrary number
};

}  // namespace LogLib
