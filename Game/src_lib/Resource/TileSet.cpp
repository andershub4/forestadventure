/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileSet.h"

#include <SFML/Graphics/Texture.hpp>

#include "Enum/TileId.h"
#include "Misc/TextureManager.h"
#include "Utils/Logger.h"

namespace FA {

const std::unordered_map<TileId, sf::IntRect> mapLookup = {{TileId::BasicGround, {208, 288, 16, 16}},
                                                           {TileId::Ground1, {240, 400, 16, 16}},
                                                           {TileId::GroundPlant, {240, 368, 16, 16}},
                                                           {TileId::GreenPlant, {208, 400, 16, 16}},
                                                           {TileId::Stone, {272, 480, 16, 16}}};

TileSet::TileSet(TextureManager& textureManager)
    : textureManager_(textureManager)
    , texture_(nullptr)
{}

TileSet::~TileSet() = default;

void TileSet::Load()
{
    texture_ = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/environment/tileset.png");
}

TileSet::Tile TileSet::GetTile(TileId id) const
{
    if (texture_ == nullptr) return {};

    auto it = mapLookup.find(id);
    if (it != mapLookup.end()) {
        return {texture_, mapLookup.at(id)};
    }
    else {
        LOG_ERROR("id: ", static_cast<unsigned int>(id), " does not exist");
        return {};
    }
}

}  // namespace FA
