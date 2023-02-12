/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "LevelCreator.h"

#include <SFML/Graphics/Sprite.hpp>

#include "Resource/Image.h"

namespace FA {

namespace World {

void LevelCreator::AddBackground(const std::vector<TileMap::TileData> &layer)
{
    layers_.push_back(layer);
}

void LevelCreator::CreateBackground(const sf::Vector2u &size, sf::RenderTexture &texture) const
{
    texture.create(size.x, size.y);

    for (const auto &layer : layers_) {
        for (const auto &data : layer) {
            auto sprite = CreateSprite(data);
            texture.draw(sprite);
        }
    }
}

std::vector<sf::Sprite> LevelCreator::CreateFringe(const std::vector<TileMap::TileData> &layer) const
{
    std::vector<sf::Sprite> fringe;

    for (const auto &data : layer) {
        auto sprite = CreateSprite(data);
        fringe.push_back(sprite);
    }

    return fringe;
}

sf::Sprite LevelCreator::CreateSprite(const TileMap::TileData &data) const
{
    Shared::Image image(data.graphic_.image_);
    sf::Sprite sprite;
    image.ApplyTo(sprite);
    sprite.setPosition(data.position_);

    return sprite;
}

}  // namespace World

}  // namespace FA
