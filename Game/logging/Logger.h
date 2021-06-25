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

    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void OpenLog(const std::string& folder, const std::string& fileName, bool toConsole);
    void CloseLog();

    template <class T, class... Rest>
    void MakeLogEntry(const Logger::LogLevel& logLevel, const std::string& func, T data, Rest... rest)
    {
        StartLine(logLevel, func);
        Log(data, rest...);
    }

private:
    std::ofstream logStream_;
    std::string filePath_;
    std::ofstream::pos_type currSize_;
    std::ofstream::pos_type maxSize_ = 1048576;  // arbitrary number
    bool toConsole_{false};

private:
    template <class T>
    void LogData(const T& data)
    {
        if (logStream_.is_open()) {
            currSize_ = (logStream_ << data << std::flush).tellp();
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
        if (toConsole_) std::cout << data;
#endif
    }

    template <class T, class... Rest>
    void Log(const T& data, Rest... rest)
    {
        LogData(data);
        Log(rest...);
    }

    template <class T>
    void Log(const T& data)
    {
        LogData(data);
        EndLine();
    }

    void StartLine(const LogLevel& logLevel, const std::string& funcName);
    void EndLine();
    void OpeningLines();
    void ClosingLines();
    std::string TimeStr();
    std::string ToStr(const LogLevel& logLevel) const;
    bool FolderExists(const std::string& folder) const;
};

}  // namespace LogLib
