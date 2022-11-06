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

namespace LogLib {

std::string Logger::ToString(const char* format, ...)
{
    std::string result;

    if (format != nullptr) {
        va_list args;
        va_start(args, format);
        char buffer[maxLogEntrySize_];
        memset(buffer, 0, maxLogEntrySize_ * sizeof(char));
        vsnprintf(buffer, maxLogEntrySize_ - 1, format, args);
        result = std::string(buffer);
        va_end(args);
    }

    return result;
}

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

void Logger::MakeLogEntry(const Logger::LogLevel& logLevel, const std::string& func, const std::string& logStr)
{
    StartLine(logLevel, func);
    Log(logStr);
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

void Logger::Log(const std::string& logStr)
{
    LogStr(logStr);
    EndLine();
}

void Logger::StartLine(const LogLevel& logLevel, const std::string& funcName)
{
    std::stringstream ss;
    ss << "[" << ToStr(logLevel) << " | " << funcName << "]: ";
    LogStr(ss.str());
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

std::string Logger::ToStr(const LogLevel& logLevel) const
{
    std::string str;

    switch (logLevel) {
        case LogLevel::Error:
            str = "ERROR";
            break;
        case LogLevel::Warning:
            str = "WARNING";
            break;
        case LogLevel::Info:
            str = "INFO";
            break;
    }

    return str;
}

bool Logger::FolderExists(const std::string& folder) const
{
    struct stat info;
    if (stat(folder.c_str(), &info) != 0) return false;

    return info.st_mode & S_IFDIR ? true : false;
}

}  // namespace LogLib
