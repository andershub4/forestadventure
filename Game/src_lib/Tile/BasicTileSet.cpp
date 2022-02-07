/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicTileSet.h"

#include "Folder.h"
#include "Resource/Frame.h"
#include "Resource/SheetManager.h"
#include "Resource/SpriteSheet.h"

namespace FA {

namespace Tile {

BasicTileSet::BasicTileSet(SheetManager &sheetManager)
    : sheetManager_(sheetManager)
    , frameHandler_()
{}

BasicTileSet::~BasicTileSet() = default;

void BasicTileSet::LoadSheet(const std::string &filePath, const sf::Vector2u &size)
{
    name_ = GetHead(filePath);
    sheetManager_.LoadSheet(name_, filePath, size);
}

Frame BasicTileSet::GetFrame(const sf::Vector2u &uvCoord) const
{
    ImageData data{name_, uvCoord, 0.0};
    return frameHandler_.MakeFrame(sheetManager_, data);
}

}  // namespace Tile

}  // namespace FA
