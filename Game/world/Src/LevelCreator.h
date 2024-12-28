/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <tuple>
#include <vector>

#include "Resource/TextureManager.h"
#include "TileMap.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;
class SpriteIf;

}  // namespace Graphic

namespace Shared {

class SheetManager;
template <class T>
class ImageAnimationIf;
struct ImageFrame;

}  // namespace Shared

namespace World {

constexpr float switchTime = 0.1f;

class LevelCreator
{
public:
    LevelCreator(const Shared::TextureManager &textureManager, const Shared::SheetManager &sheetManager);

    void AddBackground(const std::vector<TileMap::TileData> &layer);
    void CreateBackground(Graphic::RenderTargetIf &texture) const;
    std::vector<std::shared_ptr<Graphic::SpriteIf>> CreateFringe(const std::vector<TileMap::TileData> &layer) const;
    std::vector<
        std::tuple<std::shared_ptr<Shared::ImageAnimationIf<Shared::ImageFrame>>, std::shared_ptr<Graphic::SpriteIf>>>
    CreateAnimations(const std::vector<TileMap::TileData> &layer) const;

private:
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    std::vector<std::vector<TileMap::TileData>> layers_;

private:
    std::shared_ptr<Graphic::SpriteIf> CreateSprite(const TileMap::TileData &data) const;
    std::shared_ptr<Shared::ImageAnimationIf<Shared::ImageFrame>> CreateAnimation(const TileMap::TileData &data) const;
};

}  // namespace World

}  // namespace FA
