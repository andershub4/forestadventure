/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicLogger.h"

#include <fstream>
#include <string>

namespace LogLib {

class Logger : public BasicLogger
{
public:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    virtual void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole) override;
    virtual void CloseLog() override;
    virtual void MakeDebugLogEntry(const std::string& fn, const std::string& str) override;
    virtual void MakeInfoLogEntry(const std::string& fn, const std::string& str) override;
    virtual void MakeWarnLogEntry(const std::string& fn, const std::string& str) override;
    virtual void MakeErrorLogEntry(const std::string& fn, const std::string& str) override;

private:
    std::ofstream logStream_;
    std::string filePath_;
    std::ofstream::pos_type currSize_;
    std::ofstream::pos_type maxSize_ = 1048576;  // arbitrary number
    bool toConsole_{false};

private:
    enum class LogLevel { Error, Warning, Info, Debug };

    void MakeLogEntry(const Logger::LogLevel& logLevel, const std::string& fn, const std::string& str);
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
