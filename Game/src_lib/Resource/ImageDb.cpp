/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageDb.h"

#include "SheetManager.h"

namespace FA {

namespace {

SpriteSheet::SingleFrame CreateSingleFrame(const SpriteSheet& sheet, const sf::Vector2u position)
{
    SpriteSheet::SingleFrame f;

    if (sheet.IsValid()) {
        f = sheet.At(position);
    }

    return f;
}

}  // namespace

ImageDb::ImageDb(const SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{}

void ImageDb::AddImage(const ImageData& data)
{
    auto sheet = sheetManager_.GetSheet(data.sheetId_);
    auto singleFrame = CreateSingleFrame(sheet, data.position_);
    if (singleFrame.isValid_) {
        auto k = data.key_;
        AddImage(k, Image(singleFrame.texture_, singleFrame.frame_, data.rotation_));
    }
}

void ImageDb::AddImage(const std::string& k, const Image& image)
{
    map_[k] = image;
}

Image ImageDb::GetImage(const std::string& k) const
{
    return map_.at(k);
}

}  // namespace FA
