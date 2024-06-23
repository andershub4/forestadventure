/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "LevelCreator.h"

#include "RenderTargetIf.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureRect.h"
#include "Sprite.h"

namespace FA {

namespace World {

LevelCreator::LevelCreator(const Shared::TextureManager &textureManager, const Shared::SheetManager &sheetManager)
    : textureManager_(textureManager)
    , sheetManager_(sheetManager)
{}

void LevelCreator::AddBackground(const std::vector<TileMap::TileData> &layer)
{
    layers_.push_back(layer);
}

void LevelCreator::CreateBackground(Graphic::RenderTargetIf &texture) const
{
    for (const auto &layer : layers_) {
        for (const auto &data : layer) {
            auto sprite = CreateSprite(data);
            texture.draw(sprite);
        }
    }
}

std::vector<Graphic::Sprite> LevelCreator::CreateFringe(const std::vector<TileMap::TileData> &layer) const
{
    std::vector<Graphic::Sprite> fringe;

    for (const auto &data : layer) {
        auto sprite = CreateSprite(data);
        fringe.push_back(sprite);
    }

    return fringe;
}

Graphic::Sprite LevelCreator::CreateSprite(const TileMap::TileData &data) const
{
    auto imageData = data.graphic_.image_;
    auto textureRect = sheetManager_.GetRect(imageData.sheetItem_);
    const auto *texture = textureManager_.Get(textureRect.id_);
    sf::IntRect rect{textureRect.position_.x, textureRect.position_.y, textureRect.size_.x, textureRect.size_.y};
    Graphic::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(data.position_);

    return sprite;
}

}  // namespace World

}  // namespace FA
