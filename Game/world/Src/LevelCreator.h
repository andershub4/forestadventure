/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include "Resource/TextureManager.h"
#include "SfmlFwd.h"
#include "TileMap.h"

namespace FA {

namespace Graphic {

class Sprite;
class IRenderTarget;

}  // namespace Graphic

namespace Shared {

class SheetManager;

}  // namespace Shared

namespace World {

class LevelCreator
{
public:
    LevelCreator(const Shared::TextureManager &textureManager, const Shared::SheetManager &sheetManager);

    void AddBackground(const std::vector<TileMap::TileData> &layer);
    void CreateBackground(Graphic::IRenderTarget &texture) const;

    std::vector<Graphic::Sprite> CreateFringe(const std::vector<TileMap::TileData> &layer) const;

private:
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    std::vector<std::vector<TileMap::TileData>> layers_;

private:
    Graphic::Sprite CreateSprite(const TileMap::TileData &data) const;
};

}  // namespace World

}  // namespace FA
