/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "TileMapData.h"

#include "Print.h"

namespace FA {

namespace Tile {

using FA::Util::operator<<;

bool operator==(const Image& lhs, const Image& rhs)
{
    return std::tie(lhs.path_, lhs.nCols_, lhs.nRows_) == std::tie(rhs.path_, rhs.nCols_, rhs.nRows_);
}

std::ostream& operator<<(std::ostream& os, const Image& p)
{
    os << "path: " << p.path_ << " nCols: " << p.nCols_ << " nRows: " << p.nRows_;

    return os;
}

bool operator==(const Frame& lhs, const Frame& rhs)
{
    return std::tie(lhs.texturePath_, lhs.column_, lhs.row_, lhs.width_, lhs.height_) ==
           std::tie(rhs.texturePath_, rhs.column_, rhs.row_, rhs.width_, rhs.height_);
}

std::ostream& operator<<(std::ostream& os, const Frame& p)
{
    os << "texturePath: " << p.texturePath_ << " column: " << p.column_ << " row: " << p.row_ << " width: " << p.width_
       << " height: " << p.height_;

    return os;
}

bool operator==(const TileData& lhs, const TileData& rhs)
{
    return std::tie(lhs.image_, lhs.animation_) == std::tie(rhs.image_, rhs.animation_);
}

std::ostream& operator<<(std::ostream& os, const TileData& p)
{
    os << "image: " << p.image_ << " animation: " << p.animation_;

    return os;
}

bool operator==(const TileSetData& lhs, const TileSetData& rhs)
{
    return std::tie(lhs.images_, lhs.lookupTable_) == std::tie(rhs.images_, rhs.lookupTable_);
}

std::ostream& operator<<(std::ostream& os, const TileSetData& p)
{
    os << "images: " << p.images_ << " lookupTable(size=" << p.lookupTable_.size() << "): [...]";

    return os;
}

bool operator==(const TileMapData::MapProperties& lhs, const TileMapData::MapProperties& rhs)
{
    return std::tie(lhs.width_, lhs.height_, lhs.tileWidth_, lhs.tileHeight_) ==
           std::tie(rhs.width_, rhs.height_, rhs.tileWidth_, rhs.tileHeight_);
}

std::ostream& operator<<(std::ostream& os, const TileMapData::MapProperties& p)
{
    os << "width: " << p.width_ << " height: " << p.height_ << " tileWidth: " << p.tileWidth_
       << " tileHeight: " << p.tileHeight_;

    return os;
}

bool operator==(const TileMapData::Layer& lhs, const TileMapData::Layer& rhs)
{
    return std::tie(lhs.name_, lhs.tileIds_) == std::tie(rhs.name_, rhs.tileIds_);
}

std::ostream& operator<<(std::ostream& os, const TileMapData::Layer& p)
{
    os << "name: " << p.name_ << " tileIds(size=" << p.tileIds_.size() << "): [...]";

    return os;
}

bool operator==(const TileMapData::Object& lhs, const TileMapData::Object& rhs)
{
    return std::tie(lhs.typeStr_, lhs.x_, lhs.y_, lhs.width_, lhs.height_, lhs.properties_) ==
           std::tie(rhs.typeStr_, rhs.x_, rhs.y_, rhs.width_, rhs.height_, rhs.properties_);
}

std::ostream& operator<<(std::ostream& os, const TileMapData::Object& p)
{
    os << "typeStr: " << p.typeStr_ << " x: " << p.x_ << " y: " << p.y_ << " width: " << p.width_
       << " height: " << p.height_ << " properties: " << p.properties_;

    return os;
}

bool operator==(const TileMapData::ObjectGroup& lhs, const TileMapData::ObjectGroup& rhs)
{
    return std::tie(lhs.name_, lhs.objects_) == std::tie(rhs.name_, rhs.objects_);
}

std::ostream& operator<<(std::ostream& os, const TileMapData::ObjectGroup& p)
{
    os << "name: " << p.name_ << " objects(size=" << p.objects_.size() << "): [...]";

    return os;
}

bool operator==(const TileMapData& lhs, const TileMapData& rhs)
{
    return std::tie(lhs.mapProperties_, lhs.tileSets_, lhs.layers_, lhs.objectGroups_) ==
           std::tie(rhs.mapProperties_, rhs.tileSets_, rhs.layers_, rhs.objectGroups_);
}

std::ostream& operator<<(std::ostream& os, const TileMapData& p)
{
    os << "mapProperties: " << p.mapProperties_ << "\n"
       << "tileSets: " << p.tileSets_ << "\n"
       << "layers: " << p.layers_ << "\n"
       << "objectGroups(size=" << p.objectGroups_.size() << "): [...]";

    return os;
}

}  // namespace Tile

}  // namespace FA
