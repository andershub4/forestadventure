/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Logger.h"

#include <sstream>

#include "Path.h"

namespace FA {

Logger& Logger::Instance()
{
    static Logger logger(GetExePath() + "\\/log.txt");
    return logger;
}

Logger::Logger(const std::string& fileName)
    : fileName_(fileName)
{
    logStream_.open(fileName);

    if (logStream_.is_open()) {
        OpeningLines();
    }

#ifdef _DEBUG
    if (!logStream_.is_open()) {
        std::cerr << "Could not open logfile for writing" << std::endl;
    }
#endif
}

Logger::~Logger()
{
    if (logStream_.is_open()) {
        ClosingLines();
        logStream_.close();
    }
}

void Logger::StartLine(const LogLevel& logLevel, const std::string& funcName)
{
    std::stringstream ss;
    ss << "[" << ToStr(logLevel) << " | " << funcName << "]: ";
    Log(ss.str());
}

void Logger::EndLine()
{
    std::stringstream ss;
    ss << std::endl;
    Log(ss.str());
}

void Logger::OpeningLines()
{
    std::stringstream ss;
    ss << "Logfile opened - " << fileName_ << std::endl;
    ss << std::endl << std::endl;
    Log(ss.str());
}

void Logger::ClosingLines()
{
    std::stringstream ss;
    ss << std::endl << std::endl;
    ss << "Logfile closing - " << fileName_ << std::endl;
    Log(ss.str());
}

std::string Logger::ToStr(const LogLevel& logLevel) const
{
    std::string str;

    switch (logLevel) {
        case LogLevel::ERROR:
            str = "ERROR";
            break;
        case LogLevel::WARNING:
            str = "WARNING";
            break;
        case LogLevel::INFO:
            str = "INFO";
            break;
    }

    return str;
}

}  // namespace FA
