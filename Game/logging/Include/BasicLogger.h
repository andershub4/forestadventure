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
    enum class LogLevel { Error, Warning, Info };

    static std::string ToString(const char* format, ...);

    virtual void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole) = 0;
    virtual void CloseLog() = 0;
    virtual void MakeLogEntry(const BasicLogger::LogLevel& logLevel, const std::string& func,
                              const std::string& logStr) = 0;

protected:
    static constexpr int maxLogEntrySize_{40000};  // arbitrary number
};

}  // namespace LogLib
