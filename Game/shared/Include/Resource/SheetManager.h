/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "SpriteSheetIf.h"

namespace FA {

namespace Shared {

struct SheetItem;

class SheetManager
{
public:
    void AddSheet(const std::string &name, std::unique_ptr<SpriteSheetIf> sheet);
    TextureRect GetTextureRect(const SheetItem &item) const;

private:
    std::unordered_map<std::string, std::unique_ptr<SpriteSheetIf>> sheetMap_;

private:
    SpriteSheetIf *GetSheet(const std::string &sheetId) const;
};

}  // namespace Shared

}  // namespace FA
