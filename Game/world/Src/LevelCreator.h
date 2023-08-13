/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "Resource/TextureManager.h"
#include "SfmlFwd.h"
#include "TileMap.h"

namespace FA {

namespace Shared {

class SheetManager;

}  // namespace Shared

namespace World {

class LevelCreator
{
public:
    LevelCreator(const Shared::TextureManager &textureManager, const Shared::SheetManager &sheetManager);

    void AddBackground(const std::vector<TileMap::TileData> &layer);
    void CreateBackground(const sf::Vector2u &size, sf::RenderTexture &texture) const;

    std::vector<sf::Sprite> CreateFringe(const std::vector<TileMap::TileData> &layer) const;

private:
    const Shared::TextureManager &textureManager_;
    const Shared::SheetManager &sheetManager_;
    std::vector<std::vector<TileMap::TileData>> layers_;

private:
    sf::Sprite CreateSprite(const TileMap::TileData &data) const;
};

}  // namespace World

}  // namespace FA
