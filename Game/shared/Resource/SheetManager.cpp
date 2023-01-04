/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SheetManager.h"

#include "AnimationData.h"
#include "Frame.h"
#include "ImageData.h"
#include "SheetData.h"

namespace FA {

SheetManager::SheetManager(TextureManager& textureManager)
    : textureManager_(textureManager)
{}

void SheetManager::LoadSheet(const std::string& sheetPath, const SheetData& data)
{
    auto p = sheetPath + data.path_;
    LoadSheet(data.name_, p, data.size_);
}

void SheetManager::LoadSheet(const std::string& name, const std::string& p, const sf::Vector2u& size)
{
    textureManager_.Add(name, p);
    const sf::Texture* t = textureManager_.Get(name);
    SpriteSheet s(t, size);
    sheetMap_.insert({name, s});
}

std::vector<Frame> SheetManager::MakeFrames(const AnimationData& data) const
{
    auto location = data.locationData_;
    auto sheet = GetSheet(data.sheetId_);
    auto frames = CreateFrames(sheet, location.start_, location.nRects_);

    return data.mirror_ ? SpriteSheet::MirrorX(frames) : frames;
}

Frame SheetManager::MakeFrame(const ImageData& data) const
{
    auto sheet = GetSheet(data.sheetId_);
    auto frame = CreateFrame(sheet, data.position_);

    return frame;
}

Frame SheetManager::CreateFrame(const SpriteSheet& sheet, const sf::Vector2u position) const
{
    Frame f;

    if (sheet.IsValid()) {
        f = sheet.At(position);
    }

    return f;
}

std::vector<Frame> SheetManager::CreateFrames(const SpriteSheet& sheet, const sf::Vector2u start,
                                              unsigned int nRects) const
{
    std::vector<Frame> f;

    if (sheet.IsValid()) {
        f = sheet.Scan(start, nRects);
    }

    return f;
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

}  // namespace FA
