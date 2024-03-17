/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Error.h"

#include <Windows.h>

namespace FA {

namespace Util {

std::string GetLastErrorAsStr()
{
    std::string str;
    DWORD id = ::GetLastError();

    if (id != 0) {
        char* buffer = nullptr;

        size_t size =
            FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);

        str = std::string(buffer, size);
        LocalFree(buffer);
    }

    return str;
}

}  // namespace Util

}  // namespace FA
