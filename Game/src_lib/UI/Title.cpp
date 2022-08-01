/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Title.h"

#include "Util/Version.h"

namespace FA {

namespace UI {

std::string GetTitle()
{
#ifdef _DEBUG
    return std::string(FA_APP_NAME) + " v" + FA_APP_VERSION;
#else
    return std::string(FA_APP_NAME);
#endif
}

}  // namespace UI

}  // namespace FA
