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

AnimationDb::AnimationDb(SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{}

void AnimationDb::Load(EntityType entityType, const std::vector<AnimationData>& animationData)
{
    float t = 0.1f;

    for (const auto& animation : animationData) {
        auto location = animation.data_;
        auto sheet = sheetManager_.GetSheet(animation.sheetId_);
        auto data = CreateFrameData(sheet, location.start_, location.nFrames_, location.defaultFrame_);
        if (data.isValid_) {
            Key k = std::make_tuple(entityType, animation.frameType_, animation.dir_);
            auto frames = animation.mirror_ ? SpriteSheet::MirrorX(data.frames_) : data.frames_;
            AddAnimation(k, Animation(data.texture_, frames, data.defaultFrame_, t));
        }
    }
}

void AnimationDb::AddAnimation(Key k, const Animation& animation)
{
    map_[k] = animation;
}

Animation AnimationDb::GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return map_.at({entityType, frameType, faceDir});
}

}  // namespace FA
