/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <fstream>
#ifdef _DEBUG
#include <iostream>
#endif
#include <string>

namespace LogLib {

class Logger
{
public:
    enum class LogLevel { Error, Warning, Info };

    static Logger& Instance();

    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void OpenLog(const std::string& filePath);

    template <class T>
    void Log(const T& data)
    {
        if (logStream_.is_open()) {
            currSize_ = (logStream_ << data << std::flush).tellp();
            if (currSize_ > maxSize_) {
                logStream_ << std::endl << std::endl;
                logStream_ << "Logfile closing - file too large - " << fileName_ << std::endl;
#ifdef _DEBUG
                std::cout << std::endl << std::endl;
                std::cout << "Logfile closing - file too large - " << fileName_ << std::endl;
#endif
                logStream_.close();
            }
        }
#ifdef _DEBUG
        std::cout << data;
#endif
    }

    void StartLine(const LogLevel& logLevel, const std::string& funcName);
    void EndLine();

private:
    std::ofstream logStream_;
    std::string fileName_;
    std::ofstream::pos_type currSize_;
    std::ofstream::pos_type maxSize_ = 1048576;  // arbitrary number

private:
    void OpeningLines();
    void ClosingLines();
    std::string ToStr(const LogLevel& logLevel) const;
};

template <class T>
void Log(const T& data)
{
    Logger::Instance().Log(data);
    Logger::Instance().EndLine();
}

template <class T, class... Rest>
void Log(const T& data, Rest... rest)
{
    Logger::Instance().Log(data);
    Log(rest...);
}

template <class T, class... Rest>
void MakeLogEntry(const Logger::LogLevel& logLevel, const std::string& func, T data, Rest... rest)
{
    Logger::Instance().StartLine(logLevel, func);
    Log(data, rest...);
}

}  // namespace LogLib

#define OPEN_LOG(filePath) LogLib::Logger::Instance().OpenLog((filePath));

#define LOG_INFO(...) LogLib::MakeLogEntry(LogLib::Logger::LogLevel::Info, __FUNCTION__, __VA_ARGS__)
#define LOG_WARN(...) LogLib::MakeLogEntry(LogLib::Logger::LogLevel::Warning, __FUNCTION__, __VA_ARGS__)
#define LOG_ERROR(...) LogLib::MakeLogEntry(LogLib::Logger::LogLevel::Error, __FUNCTION__, __VA_ARGS__)

#define LOG_INFO_ENTER_FUNC() LOG_INFO("ENTER")
#define LOG_INFO_EXIT_FUNC() LOG_INFO("EXIT")
