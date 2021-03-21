/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileSet.h"

#include <SFML/Graphics/Texture.hpp>

#include "Enum/TileType.h"
#include "Misc/TextureManager.h"
#include "Utils/Logger.h"

namespace FA {

const std::unordered_map<TileType, sf::IntRect> mapLookup = {{TileType::BasicGround, {208, 288, 16, 16}},
                                                           {TileType::Ground1, {240, 400, 16, 16}},
                                                           {TileType::GroundPlant, {240, 368, 16, 16}},
                                                           {TileType::GreenPlant, {208, 400, 16, 16}},
                                                           {TileType::Stone, {272, 480, 16, 16}}};

TileSet::TileSet(TextureManager& textureManager)
    : textureManager_(textureManager)
    , texture_(nullptr)
{}

TileSet::~TileSet() = default;

void TileSet::Load()
{
    texture_ = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/environment/tileset.png");
}

TileSet::Tile TileSet::GetTile(TileType type) const
{
    if (texture_ == nullptr) return {};

    auto it = mapLookup.find(type);
    if (it != mapLookup.end()) {
        return {texture_, mapLookup.at(type)};
    }
    else {
        LOG_ERROR("type: ", static_cast<unsigned int>(type), " does not exist");
        return {};
    }
}

}  // namespace FA
