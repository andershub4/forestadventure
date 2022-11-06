/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <cstdarg>
#include <fstream>
#include <string>

namespace LogLib {

class Logger
{
public:
    enum class LogLevel { Error, Warning, Info };

    static std::string ToString(const char* format, ...);

    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole);
    void CloseLog();
    void MakeLogEntry(const Logger::LogLevel& logLevel, const std::string& func, const std::string& logStr);

private:
    static constexpr int maxLogEntrySize_{40000};  // arbitrary number
    std::ofstream logStream_;
    std::string filePath_;
    std::ofstream::pos_type currSize_;
    std::ofstream::pos_type maxSize_ = 1048576;  // arbitrary number
    bool toConsole_{false};

private:
    void LogStr(const std::string& logStr);
    void Log(const std::string& logStr);
    void StartLine(const LogLevel& logLevel, const std::string& funcName);
    void EndLine();
    void OpeningLines();
    void ClosingLines();
    std::string TimeStr();
    std::string ToStr(const LogLevel& logLevel) const;
    bool FolderExists(const std::string& folder) const;
};

}  // namespace LogLib
