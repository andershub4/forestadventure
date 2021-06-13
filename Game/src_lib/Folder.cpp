/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Folder.h"

#include "Logger.h"
#include "Platform/Path.h"
#include "Platform/SpecialFolder.h"
#include "Version.h"

namespace FA {

namespace {

std::string GetSpecialPath(Platform::SpecialFolder specialFolder)
{
    std::string specialPath;
    std::wstring specialPathW;
    auto result = Platform::GetSpecialPath(specialFolder, specialPathW);

    if (result.IsOk()) {
        auto result = Platform::GetShortPathNameA(specialPathW, specialPath);

        if (!result.IsOk()) LOG_ERROR("Result: ", result.errorMessage_);
    }
    else {
        LOG_ERROR("Result: ", result.errorMessage_);
    }

    return specialPath;
}

std::string GetLocalAppDataPath()
{
    return GetSpecialPath(Platform::SpecialFolder::LocalAppData);
}

std::string GetProgramDataPath()
{
    return GetSpecialPath(Platform::SpecialFolder::ProgramData);
}

std::string GetExePath()
{
    std::string exeFileName = Platform::GetExeFileName();
    std::string exePath = GetHead(exeFileName);

    return exePath;
}

std::string GetFAProgramDataPath()
{
    return GetProgramDataPath() + '/' + FA_APP_NAME + '/';
}

std::string GetFALocalAppDataPath()
{
    return GetLocalAppDataPath() + '/' + FA_APP_NAME + '/';
}

}  // namespace

std::string GetHead(const std::string& filePath)
{
    std::string result;
    const size_t index = filePath.find_last_of("\\/");

    if (index != std::string::npos) {
        result = filePath.substr(0, index);
    }

    return result;
}

std::string GetLogPath()
{
#ifdef INSTALL
    return GetFALocalAppDataPath();
#else
    return GetExePath();
#endif  // INSTALL
}

std::string GetAssetsPath()
{
#ifdef INSTALL
    return GetFAProgramDataPath() + "assets/";
#else
    return "assets/";
#endif  // INSTALL
}

}  // namespace FA
