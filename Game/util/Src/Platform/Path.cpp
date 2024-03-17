/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Platform/Path.h"

#include <shlobj.h>
#include <algorithm>
#include <iterator>

#include "Error.h"

namespace FA {

namespace Util {

Result GetShortPathNameW(const std::wstring& longPath, std::wstring& shortPath)
{
    Result result;

    int length = ::GetShortPathName(longPath.c_str(), NULL, 0);
    if (length == 0) {
        result = Result(GetLastErrorAsStr());
    }
    else {
        std::wstring str;
        str.reserve(length);
        str.resize(length - 1);

        length = ::GetShortPathName(longPath.c_str(), &str[0], length);
        if (length == 0) {
            result = Result(GetLastErrorAsStr());
        }
        else {
            shortPath = str;
        }
    }

    return result;
}

Result GetShortPathNameA(const std::wstring& longPath, std::string& shortPath)
{
    std::wstring shortPathW;
    auto result = GetShortPathNameW(longPath, shortPathW);

    if (result.IsOk()) {
        std::transform(shortPathW.begin(), shortPathW.end(), std::back_inserter(shortPath),
                       [](wchar_t c) { return (char)c; });
    }

    return result;
}

std::string GetExeFileName()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    return std::string(buffer);
}

}  // namespace Util

}  // namespace FA
