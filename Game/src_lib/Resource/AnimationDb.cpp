/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationDb.h"

#include "SheetManager.h"

namespace FA {

namespace {

SpriteSheet::FrameData CreateFrameData(const SpriteSheet& sheet, const sf::Vector2u start, unsigned int n,
                                       unsigned int defaultIndex)
{
    SpriteSheet::FrameData f;

    if (sheet.IsValid()) {
        f = sheet.Scan(start, n, defaultIndex);
    }

    return f;
}

}  // namespace

AnimationDb::AnimationDb(const SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{}

void AnimationDb::AddAnimation(const AnimationData& data)
{
    float t = 0.1f;

    auto location = data.locationData_;
    auto sheet = sheetManager_.GetSheet(data.sheetId_);
    auto frameData = CreateFrameData(sheet, location.start_, location.nFrames_, location.defaultFrame_);
    if (frameData.isValid_) {
        auto k = data.key_;
        auto frames = data.mirror_ ? SpriteSheet::MirrorX(frameData.frames_) : frameData.frames_;
        AddAnimation(k, Animation(frameData.texture_, frames, frameData.defaultFrame_, t));
    }
}

void AnimationDb::AddAnimation(const std::string& k, const Animation& animation)
{
    map_[k] = animation;
}

Animation AnimationDb::GetAnimation(const std::string& k) const
{
    return map_.at(k);
}

}  // namespace FA
