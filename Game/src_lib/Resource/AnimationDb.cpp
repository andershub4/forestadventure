/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationDb.h"

#include "EntityTextures.h"
#include "Folder.h"
#include "Logging.h"
#include "Resource/SpriteSheet.h"
#include "Resource/TextureManager.h"
#include "TextureId.h"

namespace FA {

namespace {

struct AnimationData
{
    std::string sheetId_;
    struct FrameData
    {
        sf::Vector2u start_;
        unsigned int n_;
        unsigned int defaultIndex_;
        bool mirror_;
    };

    FrameData data_;
    FrameType frameType_;
    FaceDirection dir_;
};

std::vector<AnimationData> playerData = {
    {TextureId::HeroWalkSide, {{0, 0}, 6, 0, true}, FrameType::Move, FaceDirection::Left},
    {TextureId::HeroWalkSide, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Right},
    {TextureId::HeroWalkFront, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Down},
    {TextureId::HeroWalkBack, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Up},
    {TextureId::HeroIdleSide, {{0, 0}, 1, 0, true}, FrameType::Idle, FaceDirection::Left},
    {TextureId::HeroIdleSide, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Right},
    {TextureId::HeroIdleFront, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Down},
    {TextureId::HeroIdleBack, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Up},
    {TextureId::HeroAttackSide, {{0, 0}, 3, 0, true}, FrameType::Attack, FaceDirection::Left},
    {TextureId::HeroAttackSide, {{0, 0}, 3, 0, false}, FrameType::Attack, FaceDirection::Right},
    {TextureId::HeroAttackFront, {{0, 0}, 3, 0, false}, FrameType::Attack, FaceDirection::Down},
    {TextureId::HeroAttackBack, {{0, 0}, 3, 0, false}, FrameType::Attack, FaceDirection::Up},
    {TextureId::HeroAttackWeaponSide, {{0, 0}, 3, 0, true}, FrameType::AttackWeapon, FaceDirection::Left},
    {TextureId::HeroAttackWeaponSide, {{0, 0}, 3, 0, false}, FrameType::AttackWeapon, FaceDirection::Right},
    {TextureId::HeroAttackWeaponFront, {{0, 0}, 3, 0, false}, FrameType::AttackWeapon, FaceDirection::Down},
    {TextureId::HeroAttackWeaponBack, {{0, 0}, 3, 0, false}, FrameType::AttackWeapon, FaceDirection::Up}};

std::vector<AnimationData> moleData = {
    {TextureId::MoleWalkSide, {{0, 0}, 6, 0, true}, FrameType::Move, FaceDirection::Left},
    {TextureId::MoleWalkSide, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Right},
    {TextureId::MoleWalkFront, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Down},
    {TextureId::MoleWalkBack, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Up},
    {TextureId::MoleIdleSide, {{0, 0}, 1, 0, true}, FrameType::Idle, FaceDirection::Left},
    {TextureId::MoleIdleSide, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Right},
    {TextureId::MoleIdleFront, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Down},
    {TextureId::MoleIdleBack, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Up}};

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

void AnimationDb::Load()
{
    LoadTextures();
    InitPlayer();
    InitMole();
}

void AnimationDb::LoadTextures()
{
    LOG_INFO("Load entity textures");
    auto ssPath = GetAssetsPath() + "/tiny-RPG-forest-files/PNG/spritesheets/";
    for (const auto& v : textures) {
        auto p = ssPath + v.path_;
        textureManager_.Add(v.name_, p);
        const sf::Texture* t = textureManager_.Get(v.name_);
        auto size = v.size_;
        SpriteSheet s(t, size);
        sheetMap_.insert({v.name_, s});
    }
}

void AnimationDb::InitPlayer()
{
    float t = 0.1f;

    for (const auto& item : playerData) {
        auto data =
            CreateFrameData(GetSheet(item.sheetId_), item.data_.start_, item.data_.n_, item.data_.defaultIndex_);
        if (data.isValid_) {
            Key k = std::make_tuple(EntityType::Player, item.frameType_, item.dir_);
            auto frames = item.data_.mirror_ ? SpriteSheet::MirrorX(data.frames_) : data.frames_;
            AddAnimation(k, Animation(data.texture_, frames, data.defaultFrame_, t));
        }
    }
}

void AnimationDb::InitMole()
{
    float t = 0.1f;

    for (const auto& item : moleData) {
        auto data =
            CreateFrameData(GetSheet(item.sheetId_), item.data_.start_, item.data_.n_, item.data_.defaultIndex_);
        if (data.isValid_) {
            Key k = std::make_tuple(EntityType::Mole, item.frameType_, item.dir_);
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
