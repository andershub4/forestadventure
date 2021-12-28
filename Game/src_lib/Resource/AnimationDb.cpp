/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationDb.h"

#include "Folder.h"
#include "Logging.h"
#include "SheetData.h"
#include "SheetId.h"

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

AnimationDb::AnimationDb(TextureManager& textureManager)
    : textureManager_(textureManager)
{}

void AnimationDb::Load(EntityType entityType, const std::vector<AnimationData>& animationData)
{
    LoadTextures();
    Init(entityType, animationData);
}

void AnimationDb::LoadTextures()
{
    LOG_INFO("Load entity textures");
    auto ssPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/spritesheets/";
    for (const auto& v : sheetData) {
        auto p = ssPath + v.path_;
        textureManager_.Add(v.name_, p);
        const sf::Texture* t = textureManager_.Get(v.name_);
        auto size = v.size_;
        SpriteSheet s(t, size);
        sheetMap_.insert({v.name_, s});
    }
}

void AnimationDb::Init(EntityType entityType, const std::vector<AnimationData>& animationData)
{
    float t = 0.1f;

    for (const auto& item : animationData) {
        auto data =
            CreateFrameData(GetSheet(item.sheetId_), item.data_.start_, item.data_.n_, item.data_.defaultIndex_);
        if (data.isValid_) {
            Key k = std::make_tuple(entityType, item.frameType_, item.dir_);
            auto frames = item.data_.mirror_ ? SpriteSheet::MirrorX(data.frames_) : data.frames_;
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

SpriteSheet AnimationDb::GetSheet(const std::string& name) const
{
    auto it = sheetMap_.find(name);

    if (it != sheetMap_.end()) {
        return sheetMap_.at(name);
    }

    return SpriteSheet();
}

}  // namespace FA
