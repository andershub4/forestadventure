/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "Platform/Result.h"

namespace FA {

namespace Platform {

enum class SpecialFolder { Documents, LocalAppData, ProgramData };

Result GetSpecialPath(SpecialFolder specialFolder, std::wstring& specialPath);

}  // namespace Platform

}  // namespace FA
