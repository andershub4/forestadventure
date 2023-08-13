/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Resource/SheetManager.h"

#include <sstream>

#include "Logging.h"
#include "Resource/AnimationData.h"
#include "Resource/ImageData.h"
#include "Resource/SheetData.h"

namespace FA {

namespace Shared {

void SheetManager::AddSheet(const std::string& name, ResourceId textureId, const sf::Vector2u& textureSize,
                            const sf::Vector2u& rectCount)
{
    SpriteSheet s(textureId, textureSize, rectCount);
    sheetMap_.insert({name, s});
}

std::vector<TextureRect> SheetManager::MakeRects(const AnimationData& data) const
{
    auto location = data.locationData_;
    auto sheet = GetSheet(data.sheetId_);
    auto rects = CreateRects(sheet, location.start_, location.nRects_);

    return data.mirror_ ? SpriteSheet::MirrorX(rects) : rects;
}

TextureRect SheetManager::MakeRect(const ImageData& data) const
{
    auto sheet = GetSheet(data.sheetId_);
    auto rect = CreateRect(sheet, data.position_);

    return rect;
}

TextureRect SheetManager::CreateRect(const SpriteSheet& sheet, const sf::Vector2u position) const
{
    TextureRect rect;

    if (sheet.IsValid()) {
        rect = sheet.At(position);
    }

    return rect;
}

std::vector<TextureRect> SheetManager::CreateRects(const SpriteSheet& sheet, const sf::Vector2u start,
                                                   unsigned int nRects) const
{
    std::vector<TextureRect> rects;

    if (sheet.IsValid()) {
        rects = sheet.Scan(start, nRects);
    }

    return rects;
}

SpriteSheet SheetManager::GetSheet(const std::string& name) const
{
    auto it = sheetMap_.find(name);

    if (it != sheetMap_.end()) {
        return sheetMap_.at(name);
    }
    else {
        LOG_ERROR("name %s not found", name.c_str());
        return SpriteSheet();
    }
}

}  // namespace Shared

}  // namespace FA
