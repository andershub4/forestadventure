/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace FA {

namespace Shared {

struct AnimationData;
struct ImageData;
struct TextureRect;
class SpriteSheetIf;

class SheetManager
{
public:
    void AddSheet(const std::string &name, std::unique_ptr<SpriteSheetIf> sheet);
    std::vector<TextureRect> MakeRects(const AnimationData &data) const;
    TextureRect MakeRect(const ImageData &data) const;

private:
    std::unordered_map<std::string, std::unique_ptr<SpriteSheetIf>> sheetMap_;

private:
    SpriteSheetIf *GetSheet(const std::string &name) const;
    std::vector<TextureRect> MirrorX(const std::vector<TextureRect> &rects) const;
};

}  // namespace Shared

}  // namespace FA
