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
struct AnimationData;
struct ImageData;

class SheetManager
{
public:
    SheetManager(TextureManager &textureManager);
    void LoadSheet(const std::string &sheetPath, const SheetData &data);
    void LoadSheet(const std::string &name, const std::string &p, const sf::Vector2u &size);
    std::vector<Frame> MakeFrames(const AnimationData &data) const;
    Frame MakeFrame(const ImageData &data) const;

private:
    TextureManager &textureManager_;
    std::unordered_map<std::string, SpriteSheet> sheetMap_;

private:
    SpriteSheet GetSheet(const std::string &name) const;
    Frame CreateFrame(const SpriteSheet &sheet, const sf::Vector2u position) const;
    std::vector<Frame> CreateFrames(const SpriteSheet &sheet, const sf::Vector2u start, unsigned int nRects) const;
};

}  // namespace FA
