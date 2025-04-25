/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

/*
 *	This file is written as a part of of the shared_test library.
 *	In order to use link time substitution for mocking purpose,
 *	this file must be added (using Add->Existing Item...) to your test project
 */

#include "Mock/LoggerMock.h"

namespace FA {

namespace Shared {

LoggerMock* LoggerMock::instance_;

void MakeDebugLogEntry(const std::string& fn, const std::string& str)
{
    // No need to test DebugLogEntry
}

void MakeInfoLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance().MakeInfoLogEntry(str);
}

void MakeWarnLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance().MakeWarnLogEntry(str);
}

void MakeErrorLogEntry(const std::string& fn, const std::string& str)
{
    LoggerMock::Instance().MakeErrorLogEntry(str);
}

}  // namespace Shared

}  // namespace FA
