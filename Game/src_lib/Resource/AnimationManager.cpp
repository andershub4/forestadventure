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
#include "Misc/TextureManager.h"
#include "SpriteSheet.h"

namespace FA {

AnimationManager::AnimationManager(TextureManager& textureManager)
    : textureManager_(textureManager)
{}

AnimationManager::~AnimationManager() = default;

void AnimationManager::RegisterFactories()
{
    RegisterPlayerFactory();
    RegisterMoleFactory();
}

void AnimationManager::RegisterPlayerFactory()
{
    AnimationFactory factory(0.1f);
    std::string ssPath = GetSpriteSheetPath();

    auto textureWalkSide = textureManager_.GetTexture(ssPath + "hero/walk/hero-walk-side.png");
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("heroWalkSide", textureWalkSide, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_,
                                      true);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront = textureManager_.GetTexture(ssPath + "hero/walk/hero-walk-front.png");
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("heroWalkFront", textureWalkFront, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack = textureManager_.GetTexture(ssPath + "hero/walk/hero-back-walk.png");
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("heroWalkBack", textureWalkBack, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureAttackSide = textureManager_.GetTexture(ssPath + "hero/attack/hero-attack-side.png");
    if (textureAttackSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackSide", textureAttackSide, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        factory.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_,
                                      true);
        factory.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackFront = textureManager_.GetTexture(ssPath + "hero/attack/hero-attack-front.png");
    if (textureAttackFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackFront", textureAttackFront, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        factory.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackBack = textureManager_.GetTexture(ssPath + "hero/attack/hero-attack-back.png");
    if (textureAttackBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackBack", textureAttackBack, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        factory.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureAttackSideWeapon =
        textureManager_.GetTexture(ssPath + "hero/attack-weapon/hero-attack-side-weapon.png");
    if (textureAttackSideWeapon != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponSide", textureAttackSideWeapon, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        factory.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Left, f.texture_, f.frames_,
                                      f.defaultFrame_, true);
        factory.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Right, f.texture_, f.frames_,
                                      f.defaultFrame_);
    }
    auto textureAttackFrontWeapon =
        textureManager_.GetTexture(ssPath + "hero/attack-weapon/hero-attack-front-weapon.png");
    if (textureAttackFrontWeapon != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponFront", textureAttackFrontWeapon, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        factory.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Down, f.texture_, f.frames_,
                                      f.defaultFrame_);
    }
    auto textureAttackBackWeapon =
        textureManager_.GetTexture(ssPath + "hero/attack-weapon/hero-attack-back-weapon.png");
    if (textureAttackBackWeapon != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponBack", textureAttackBackWeapon, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        factory.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Up, f.texture_, f.frames_,
                                      f.defaultFrame_);
    }

    auto textureIdleSide = textureManager_.GetTexture(ssPath + "hero/idle/hero-idle-side.png");
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("heroIdleSide", textureIdleSide, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_,
                                      true);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront = textureManager_.GetTexture(ssPath + "hero/idle/hero-idle-front.png");
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("heroIdleFront", textureIdleFront, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack = textureManager_.GetTexture(ssPath + "hero/idle/hero-idle-back.png");
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("heroIdleBack", textureIdleBack, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    map_[AnimationType::Player] = factory;
}

void AnimationManager::RegisterMoleFactory()
{
    AnimationFactory factory(0.1f);
    std::string ssPath = GetSpriteSheetPath();

    auto textureWalkSide = textureManager_.GetTexture(ssPath + "mole/walk/mole-walk-side.png");
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("moleWalkSide", textureWalkSide, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_,
                                      true);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront = textureManager_.GetTexture(ssPath + "mole/walk/mole-walk-front.png");
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("moleWalkFront", textureWalkFront, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack = textureManager_.GetTexture(ssPath + "mole/walk/mole-walk-back.png");
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("moleWalkBack", textureWalkBack, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        factory.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureIdleSide = textureManager_.GetTexture(ssPath + "mole/idle/mole-idle-side.png");
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("moleIdleSide", textureIdleSide, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, f.texture_, f.frames_, f.defaultFrame_,
                                      true);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront = textureManager_.GetTexture(ssPath + "mole/idle/mole-idle-front.png");
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("moleIdleFront", textureIdleFront, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack = textureManager_.GetTexture(ssPath + "mole/idle/mole-idle-back.png");
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("moleIdleBack", textureIdleBack, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        factory.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    map_[AnimationType::Mole] = factory;
}

std::string AnimationManager::GetSpriteSheetPath() const
{
    return GetAssetsPath() + "tiny-RPG-forest-files/PNG/spritesheets/";
}

AnimationFactory AnimationManager::GetFactory(AnimationType type) const
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

}  // namespace FA
