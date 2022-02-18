/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SheetManager.h"

#include "SheetData.h"

namespace FA {

namespace {

}  // namespace

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

SpriteSheet SheetManager::GetSheet(const std::string& name) const
{
    auto it = sheetMap_.find(name);

    if (it != sheetMap_.end()) {
        return sheetMap_.at(name);
    }

    return SpriteSheet();
}

}  // namespace FA
