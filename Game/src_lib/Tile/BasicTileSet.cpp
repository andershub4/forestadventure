/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicTileSet.h"

#include "Resource/Frame.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"

namespace FA {

namespace Tile {

BasicTileSet::BasicTileSet(SheetManager &sheetManager)
    : sheetManager_(sheetManager)
{}

BasicTileSet::~BasicTileSet() = default;

void BasicTileSet::LoadSheet(const std::string &filePath, const sf::Vector2u &size)
{
    sheetManager_.LoadSheet(filePath, filePath, size);
}

Frame BasicTileSet::GetFrame(const std::string &filePath, const sf::Vector2u &uvCoord) const
{
    ImageData data{filePath, uvCoord};
    return sheetManager_.MakeFrame(data);
}

}  // namespace Tile

}  // namespace FA
