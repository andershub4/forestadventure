/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SpecialFolder.h"

#include <shlobj.h>
#include <sstream>

namespace FA {

namespace Platform {

namespace {

GUID Win32FolderGUI(SpecialFolder specialFolder)
{
    switch (specialFolder) {
        case SpecialFolder::Documents:
            return FOLDERID_Documents;  // CSIDL_PERSONAL
        case SpecialFolder::LocalAppData:
            return FOLDERID_LocalAppData;  // CSIDL_LOCAL_APPDATA
        case SpecialFolder::ProgramData:
            return FOLDERID_ProgramData;  // CSIDL_COMMON_APPDATA
        default:
            return FOLDERID_Documents;  // CSIDL_PERSONAL
    }
}

}  // namespace

Result GetSpecialPath(SpecialFolder specialFolder, std::wstring& specialPath)
{
    Result result;
    LPWSTR wszPath;
    auto folderGUI = Win32FolderGUI(specialFolder);

    if (SUCCEEDED(SHGetKnownFolderPath(folderGUI, 0, NULL, &wszPath))) {
        specialPath = std::wstring(wszPath);
    }
    else {
        std::stringstream ss;
        ss << "SHGetKnownFolderPath failed, specialFolder: " << static_cast<int>(specialFolder);
        result = Result(ss.str());
    }
    CoTaskMemFree(wszPath);

    return result;
}

}  // namespace Platform

}  // namespace FA
