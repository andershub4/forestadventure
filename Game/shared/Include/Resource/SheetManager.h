/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "Resource/SpriteSheet.h"

namespace FA {

namespace Shared {

struct AnimationData;
struct ImageData;
struct TextureRect;

class SheetManager
{
public:
    void AddSheet(const std::string &name, const SpriteSheet &sheet);
    std::vector<TextureRect> MakeRects(const AnimationData &data) const;
    TextureRect MakeRect(const ImageData &data) const;

private:
    std::unordered_map<std::string, SpriteSheet> sheetMap_;

private:
    SpriteSheet GetSheet(const std::string &name) const;
    std::vector<TextureRect> MirrorX(const std::vector<TextureRect> &rects) const;
};

}  // namespace Shared

}  // namespace FA
