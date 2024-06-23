/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Resource/SheetManager.h"

#include "Logging.h"
#include "Resource/SheetItem.h"
#include "Resource/SpriteSheet.h"
#include "Resource/TextureRect.h"

namespace FA {

namespace Shared {

void SheetManager::AddSheet(const std::string& name, std::unique_ptr<SpriteSheetIf> sheet)
{
    sheetMap_.insert({name, std::move(sheet)});
}

TextureRect SheetManager::GetTextureRect(const SheetItem& item) const
{
    auto sheet = GetSheet(item.id_);
    if (sheet != nullptr) {
        auto rect = sheet->At(item.position_);
        return rect;
    }

    return {};
}

SpriteSheetIf* SheetManager::GetSheet(const std::string& sheetId) const
{
    auto it = sheetMap_.find(sheetId);

    if (it != sheetMap_.end()) {
        return sheetMap_.at(sheetId).get();
    }
    else {
        LOG_ERROR("%s not found", DUMP(sheetId));
        return nullptr;
    }
}

}  // namespace Shared

}  // namespace FA
