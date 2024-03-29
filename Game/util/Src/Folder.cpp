/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Folder.h"

#include "Platform/Path.h"
#include "Platform/SpecialFolder.h"
#include "Version.h"

namespace FA {

namespace Util {

namespace {

std::string GetSpecialPath(SpecialFolder specialFolder)
{
    std::string specialPath;
    std::wstring specialPathW;
    auto result = GetSpecialPath(specialFolder, specialPathW);

    if (result.IsOk()) {
        auto result = GetShortPathNameA(specialPathW, specialPath);
    }

    return specialPath;
}

std::string GetLocalAppDataPath()
{
    return GetSpecialPath(SpecialFolder::LocalAppData);
}

std::string GetProgramDataPath()
{
    return GetSpecialPath(SpecialFolder::ProgramData);
}

std::string GetExePath()
{
    std::string exeFileName = GetExeFileName();
    std::string exePath = GetHead(exeFileName);

    return exePath;
}

std::string GetFAProgramDataPath()
{
    std::string p;
    if (!GetProgramDataPath().empty()) p = GetProgramDataPath() + '/' + FA_APP_NAME;

    return p;
}

std::string GetFALocalAppDataPath()
{
    std::string p;
    if (!GetLocalAppDataPath().empty()) p = GetLocalAppDataPath() + '/' + FA_APP_NAME;

    return p;
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
    std::string p;
#ifdef INSTALL
    if (!GetFALocalAppDataPath().empty()) p = GetFALocalAppDataPath() + "/logs";
#else
    p = GetExePath();
#endif  // INSTALL
    return p;
}

std::string GetAssetsPath()
{
    std::string p;
#ifdef INSTALL
    if (!GetFAProgramDataPath().empty()) p = GetFAProgramDataPath() + "/assets";
#else
    p = "assets";
#endif  // INSTALL
    return p;
}

}  // namespace Util

}  // namespace FA
