/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logger.h"

#include <sys/stat.h>
#include <chrono>
#include <sstream>
#ifdef _DEBUG
#include <iostream>
#endif

#include "Entry.h"
#include "LogLevel.h"

namespace FA {

namespace Util {

Logger::Logger() = default;

Logger::~Logger()
{
    CloseLog();
}

void Logger::OpenLog(const std::string& folder, const std::string& fileName, bool toConsole)
{
    if (!FolderExists(folder)) return;

    toConsole_ = toConsole;
    filePath_ = folder + '/' + fileName;
    logStream_.open(filePath_);

    if (logStream_.is_open()) {
        OpeningLines();
    }

#ifdef _DEBUG
    if (!logStream_.is_open()) {
        std::cerr << "Could not open logfile for writing" << std::endl;
    }
#endif
}

void Logger::CloseLog()
{
    if (logStream_.is_open()) {
        ClosingLines();
        logStream_.close();
    }
}

void Logger::MakeDebugLogEntry(const std::string& fn, const std::string& logStr)
{
    LogEntry({LogLevel::Debug, fn, logStr});
}

void Logger::MakeInfoLogEntry(const std::string& fn, const std::string& logStr)
{
    LogEntry({LogLevel::Info, fn, logStr});
}

void Logger::MakeWarnLogEntry(const std::string& fn, const std::string& logStr)
{
    LogEntry({LogLevel::Warn, fn, logStr});
}

void Logger::MakeErrorLogEntry(const std::string& fn, const std::string& logStr)
{
    LogEntry({LogLevel::Error, fn, logStr});
}

void Logger::LogStr(const std::string& logStr)
{
    if (logStream_.is_open()) {
        currSize_ = (logStream_ << logStr << std::flush).tellp();
        if (currSize_ > maxSize_) {
            logStream_ << std::endl << std::endl;
            logStream_ << "Logfile closing - file too large - " << filePath_ << std::endl;
#ifdef _DEBUG
            std::cout << std::endl << std::endl;
            std::cout << "Logfile closing - file too large - " << filePath_ << std::endl;
#endif
            logStream_.close();
        }
    }
#ifdef _DEBUG
    if (toConsole_) std::cout << logStr;
#endif
}

void Logger::LogEntry(const Entry& entry)
{
    LogStr(entry.Str());
    EndLine();
}

void Logger::EndLine()
{
    std::stringstream ss;
    ss << std::endl;
    LogStr(ss.str());
}

void Logger::OpeningLines()
{
    std::stringstream ss;
    ss << "Log file open - " << TimeStr();
    ss << "Log file path - " << filePath_ << std::endl;
    ss << std::endl << std::endl;
    LogStr(ss.str());
}

void Logger::ClosingLines()
{
    std::stringstream ss;
    ss << std::endl << std::endl;
    ss << "Log file close - " << TimeStr();
    LogStr(ss.str());
}

std::string Logger::TimeStr()
{
    std::string str;
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    char timeStr[50] = {};
    auto e = ctime_s(timeStr, 50, &now_t);
    if (!e) str = timeStr;

    return str;
}

bool Logger::FolderExists(const std::string& folder) const
{
    struct stat info;
    if (stat(folder.c_str(), &info) != 0) return false;

    return info.st_mode & S_IFDIR ? true : false;
}

}  // namespace Util

}  // namespace FA
