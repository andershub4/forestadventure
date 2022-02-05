/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Resource/TextureManager.h"

namespace FA {

namespace Tile {

struct Image
{
    sf::Vector2i size_;
    sf::IntRect uvRect_;
    const sf::Texture *texture_ = nullptr;
};

struct Tile
{
    Image image_;
};

class BasicTileSet
{
public:
    BasicTileSet(TextureManager &textureManager);
    virtual ~BasicTileSet();

    virtual void Load() = 0;
    virtual Tile GetTile(int id) const = 0;

protected:
    Image LoadImage(const std::string &filePath, int w, int h);

private:
    TextureManager &textureManager_;

private:
    const sf::Texture *LoadTexture(const std::string &textureFilePath);
};

}  // namespace Tile

}  // namespace FA
