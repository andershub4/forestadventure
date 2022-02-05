/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicTileSet.h"

#include "Folder.h"

namespace FA {

namespace Tile {

BasicTileSet::BasicTileSet(TextureManager &textureManager)
    : textureManager_(textureManager)
{}

BasicTileSet::~BasicTileSet() = default;

Image BasicTileSet::LoadImage(const std::string &filePath, int w, int h)
{
    Image i;
    i.texture_ = LoadTexture(filePath);
    i.size_ = {w, h};
    i.uvRect_ = {0, 0, w, h};

    return i;
}

const sf::Texture *BasicTileSet::LoadTexture(const std::string &textureFilePath)
{
    auto name = GetHead(textureFilePath);
    textureManager_.Add(name, textureFilePath);
    return textureManager_.Get(name);
}

}  // namespace Tile

}  // namespace FA
