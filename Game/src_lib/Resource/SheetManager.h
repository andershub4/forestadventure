/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "Resource/SpriteSheet.h"
#include "Resource/TextureManager.h"

namespace FA {

struct SheetData;

class SheetManager
{
public:
    SheetManager(TextureManager &textureManager);
    void LoadSheet(const SheetData &data);
    void LoadSheet(const std::string &name, const std::string &p, const sf::Vector2u &size);
    SpriteSheet GetSheet(const std::string &name) const;

private:
    TextureManager &textureManager_;
    std::unordered_map<std::string, SpriteSheet> sheetMap_;
};

}  // namespace FA
