/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Resource/TextureManager.h"
#include "TileMap.h"

namespace FA {

namespace Graphic {

class Sprite;
class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

class SheetManager;
class ImageAnimation;

}  // namespace Shared

namespace World {

constexpr float switchTime = 0.1f;

class LevelCreator
{
public:
    LevelCreator(const Shared::TextureManager &textureManager, const Shared::SheetManager &sheetManager);

    void AddBackground(const std::vector<TileMap::TileData> &layer);
    void CreateBackground(Graphic::RenderTargetIf &texture) const;

    std::vector<Graphic::Sprite> CreateFringe(const std::vector<TileMap::TileData> &layer) const;
    std::vector<Shared::ImageAnimation> CreateAnimations(const std::vector<TileMap::TileData> &layer) const;

private:
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    std::vector<std::vector<TileMap::TileData>> layers_;

private:
    Graphic::Sprite CreateSprite(const TileMap::TileData &data) const;
    Shared::ImageAnimation CreateAnimation(const TileMap::TileData &data) const;
};

}  // namespace World

}  // namespace FA
