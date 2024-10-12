/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "LevelCreator.h"

#include "Animation/ImageAnimation.h"
#include "RenderTargetIf.h"
#include "Resource/SheetManager.h"
#include "Resource/TextureRect.h"
#include "Sequence.h"
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

std::vector<Shared::ImageAnimation> LevelCreator::CreateAnimations(const std::vector<TileMap::TileData> &layer) const
{
    std::vector<Shared::ImageAnimation> animations;

    for (const auto &data : layer) {
        auto animation = CreateAnimation(data);
        animations.push_back(animation);
    }

    return animations;
}

Graphic::Sprite LevelCreator::CreateSprite(const TileMap::TileData &data) const
{
    auto imageData = data.graphic_.image_;
    auto textureRect = sheetManager_.GetTextureRect(imageData.sheetItem_);
    const auto *texture = textureManager_.Get(textureRect.id_);
    Graphic::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setTextureRect(textureRect.rect_);
    sprite.setPosition(data.position_);

    return sprite;
}

Shared::ImageAnimation LevelCreator::CreateAnimation(const TileMap::TileData &data) const
{
    float t = switchTime;
    auto seq = std::make_shared<Shared::Sequence<Shared::ImageFrame>>(t);
    for (const auto &image : data.graphic_.animation_) {
        auto textureRect = sheetManager_.GetTextureRect(image.sheetItem_);
        auto textureSize = sf::Vector2i(textureRect.rect_.width, textureRect.rect_.height);
        const auto *texture = textureManager_.Get(textureRect.id_);
        sf::Vector2i center = textureSize / 2;
        seq->Add({texture, textureRect.rect_, static_cast<sf::Vector2f>(center)});
    }

    auto animation = Shared::ImageAnimation(std::make_shared<Graphic::Sprite>(), seq);
    animation.SetPosition(data.position_);
    animation.Start();

    return animation;
}

}  // namespace World

}  // namespace FA
