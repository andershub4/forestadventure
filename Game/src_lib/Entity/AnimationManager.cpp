/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationManager.h"

#include <SFML/Graphics/Texture.hpp>

#include "Enum/AnimationType.h"
#include "Folder.h"
#include "Logging.h"
#include "Resource/SpriteSheet.h"
#include "Resource/TextureManager.h"
#include "TextureId.h"

namespace FA {

namespace Entity {

AnimationManager::AnimationManager(TextureManager& textureManager)
    : textureManager_(textureManager)
{}

AnimationManager::~AnimationManager() = default;

void AnimationManager::RegisterDBs()
{
    RegisterPlayerDB();
    RegisterMoleDB();
}

void AnimationManager::RegisterPlayerDB()
{
    AnimationDB db(0.1f);

    auto textureWalkSide = textureManager_.Get(TextureId::HeroWalkSide);
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("heroWalkSide", textureWalkSide, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_, true);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront = textureManager_.Get(TextureId::HeroWalkFront);
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("heroWalkFront", textureWalkFront, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack = textureManager_.Get(TextureId::HeroWalkBack);
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("heroWalkBack", textureWalkBack, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureAttackSide = textureManager_.Get(TextureId::HeroAttackSide);
    if (textureAttackSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackSide", textureAttackSide, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_, true);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackFront = textureManager_.Get(TextureId::HeroAttackFront);
    if (textureAttackFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackFront", textureAttackFront, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackBack = textureManager_.Get(TextureId::HeroAttackBack);
    if (textureAttackBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackBack", textureAttackBack, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureAttackWeaponSide = textureManager_.Get(TextureId::HeroAttackWeaponSide);
    if (textureAttackWeaponSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponSide", textureAttackWeaponSide, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_,
                                 true);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackWeaponFront = textureManager_.Get(TextureId::HeroAttackWeaponFront);
    if (textureAttackWeaponFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponFront", textureAttackWeaponFront, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackWeaponBack = textureManager_.Get(TextureId::HeroAttackWeaponBack);
    if (textureAttackWeaponBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponBack", textureAttackWeaponBack, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureIdleSide = textureManager_.Get(TextureId::HeroIdleSide);
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("heroIdleSide", textureIdleSide, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_, true);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront = textureManager_.Get(TextureId::HeroIdleFront);
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("heroIdleFront", textureIdleFront, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack = textureManager_.Get(TextureId::HeroIdleBack);
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("heroIdleBack", textureIdleBack, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    map_[AnimationType::Player] = db;
}

void AnimationManager::RegisterMoleDB()
{
    AnimationDB db(0.1f);

    auto textureWalkSide = textureManager_.Get(TextureId::MoleWalkSide);
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("moleWalkSide", textureWalkSide, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_, true);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront = textureManager_.Get(TextureId::MoleWalkFront);
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("moleWalkFront", textureWalkFront, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack = textureManager_.Get(TextureId::MoleWalkBack);
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("moleWalkBack", textureWalkBack, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureIdleSide = textureManager_.Get(TextureId::MoleIdleSide);
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("moleIdleSide", textureIdleSide, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_, true);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront = textureManager_.Get(TextureId::MoleIdleFront);
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("moleIdleFront", textureIdleFront, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack = textureManager_.Get(TextureId::MoleIdleBack);
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("moleIdleBack", textureIdleBack, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    map_[AnimationType::Mole] = db;
}

AnimationDB AnimationManager::GetDB(AnimationType type) const
{
    auto it = map_.find(type);
    if (it != map_.end()) {
        return map_.at(type);
    }
    else {
        LOG_ERROR("type: ", static_cast<unsigned int>(type), " does not exist");
        return {};
    }
}

}  // namespace Entity

}  // namespace FA
