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
    {SheetId::HeroWalkSide, {{0, 0}, 6, 0, true}, FrameType::Move, FaceDirection::Left},
    {SheetId::HeroWalkSide, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Right},
    {SheetId::HeroWalkFront, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Down},
    {SheetId::HeroWalkBack, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Up},
    {SheetId::HeroIdleSide, {{0, 0}, 1, 0, true}, FrameType::Idle, FaceDirection::Left},
    {SheetId::HeroIdleSide, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Right},
    {SheetId::HeroIdleFront, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Down},
    {SheetId::HeroIdleBack, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Up},
    {SheetId::HeroAttackSide, {{0, 0}, 3, 0, true}, FrameType::Attack, FaceDirection::Left},
    {SheetId::HeroAttackSide, {{0, 0}, 3, 0, false}, FrameType::Attack, FaceDirection::Right},
    {SheetId::HeroAttackFront, {{0, 0}, 3, 0, false}, FrameType::Attack, FaceDirection::Down},
    {SheetId::HeroAttackBack, {{0, 0}, 3, 0, false}, FrameType::Attack, FaceDirection::Up},
    {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0, true}, FrameType::AttackWeapon, FaceDirection::Left},
    {SheetId::HeroAttackWeaponSide, {{0, 0}, 3, 0, false}, FrameType::AttackWeapon, FaceDirection::Right},
    {SheetId::HeroAttackWeaponFront, {{0, 0}, 3, 0, false}, FrameType::AttackWeapon, FaceDirection::Down},
    {SheetId::HeroAttackWeaponBack, {{0, 0}, 3, 0, false}, FrameType::AttackWeapon, FaceDirection::Up}};

std::vector<AnimationData> moleData = {
    {SheetId::MoleWalkSide, {{0, 0}, 6, 0, true}, FrameType::Move, FaceDirection::Left},
    {SheetId::MoleWalkSide, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Right},
    {SheetId::MoleWalkFront, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Down},
    {SheetId::MoleWalkBack, {{0, 0}, 6, 0, false}, FrameType::Move, FaceDirection::Up},
    {SheetId::MoleIdleSide, {{0, 0}, 1, 0, true}, FrameType::Idle, FaceDirection::Left},
    {SheetId::MoleIdleSide, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Right},
    {SheetId::MoleIdleFront, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Down},
    {SheetId::MoleIdleBack, {{0, 0}, 1, 0, false}, FrameType::Idle, FaceDirection::Up}};

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
    for (const auto& v : sheetData) {
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
