/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Resource/SheetManager.h"

#include "Logging.h"
#include "Resource/AnimationData.h"
#include "Resource/ImageData.h"
#include "Resource/TextureRect.h"

namespace FA {

namespace Shared {

void SheetManager::AddSheet(const std::string& name, const SpriteSheet& sheet)
{
    sheetMap_.insert({name, sheet});
}

std::vector<TextureRect> SheetManager::MakeRects(const AnimationData& data) const
{
    auto location = data.locationData_;
    auto sheet = GetSheet(data.sheetId_);
    auto rects = sheet.Scan(location.start_, location.nRects_);

    return data.mirror_ ? MirrorX(rects) : rects;
}

TextureRect SheetManager::MakeRect(const ImageData& data) const
{
    auto sheet = GetSheet(data.sheetId_);
    auto rect = sheet.At(data.position_);

    return rect;
}

SpriteSheet SheetManager::GetSheet(const std::string& name) const
{
    auto it = sheetMap_.find(name);

    if (it != sheetMap_.end()) {
        return sheetMap_.at(name);
    }
    else {
        LOG_ERROR("%s not found", DUMP(name));
        return SpriteSheet();
    }
}

std::vector<TextureRect> SheetManager::MirrorX(const std::vector<TextureRect>& rects) const
{
    std::vector<TextureRect> mirrorRects;

    for (const auto& rect : rects) {
        TextureRect r = rect;
        r.position_.x = r.position_.x + r.size_.x;
        r.size_.x = -rect.size_.x;
        mirrorRects.push_back(r);
    }

    return mirrorRects;
}

}  // namespace Shared

}  // namespace FA
