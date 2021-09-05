/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AnimationDb.h"

#include "Entity/TextureId.h"
#include "Logging.h"
#include "Resource/SpriteSheet.h"
#include "Resource/TextureManager.h"

namespace {

FA::SpriteSheet::FrameData CreateFrameData(const sf::Texture* t, const sf::Vector2u& sheetSize,
                                           const sf::Vector2u start, unsigned int n, unsigned int defaultIndex)
{
    if (t != nullptr) {
        FA::SpriteSheet spriteSheet(t, sheetSize);
        auto f = spriteSheet.Scan(start, n, defaultIndex);
        return f;
    }

    return FA::SpriteSheet::FrameData();
}

}  // namespace

namespace FA {

namespace Entity {

AnimationDb::AnimationDb(const TextureManager& textureManager)
    : textureManager_(textureManager)
{}

void AnimationDb::Init()
{
    InitPlayer();
    InitMole();
}

Animation AnimationDb::GetAnimation(EntityType entityType, FrameType frameType, FaceDirection faceDir) const
{
    return map_.at({entityType, frameType, faceDir});
}

void AnimationDb::InitPlayer()
{
    InitPlayerMove();
    InitPlayerIdle();
    InitPlayerAttack();
    InitPlayerAttackWeapon();
}

void AnimationDb::InitPlayerMove()
{
    float t = 0.1f;
    Key k = std::make_tuple(EntityType::Player, FrameType::Move, FaceDirection::Left);

    auto side = CreateFrameData(GetTexture(TextureId::HeroWalkSide), {6, 1}, {0, 0}, 6, 0);
    if (side.isValid_) {
        std::get<2>(k) = FaceDirection::Left;
        AddAnimation(k, Animation(side.texture_, SpriteSheet::MirrorX(side.frames_), side.defaultFrame_, t));
        std::get<2>(k) = FaceDirection::Right;
        AddAnimation(k, Animation(side.texture_, side.frames_, side.defaultFrame_, t));
    }
    auto front = CreateFrameData(GetTexture(TextureId::HeroWalkFront), {6, 1}, {0, 0}, 6, 0);
    if (front.isValid_) {
        std::get<2>(k) = FaceDirection::Down;
        AddAnimation(k, Animation(front.texture_, front.frames_, front.defaultFrame_, t));
    }
    auto back = CreateFrameData(GetTexture(TextureId::HeroWalkBack), {6, 1}, {0, 0}, 6, 0);
    if (back.isValid_) {
        std::get<2>(k) = FaceDirection::Up;
        AddAnimation(k, Animation(back.texture_, back.frames_, back.defaultFrame_, t));
    }
}

void AnimationDb::InitPlayerIdle()
{
    float t = 0.1f;
    Key k = std::make_tuple(EntityType::Player, FrameType::Idle, FaceDirection::Left);

    auto side = CreateFrameData(GetTexture(TextureId::HeroIdleSide), {1, 1}, {0, 0}, 1, 0);
    if (side.isValid_) {
        std::get<2>(k) = FaceDirection::Left;
        AddAnimation(k, Animation(side.texture_, SpriteSheet::MirrorX(side.frames_), side.defaultFrame_, t));
        std::get<2>(k) = FaceDirection::Right;
        AddAnimation(k, Animation(side.texture_, side.frames_, side.defaultFrame_, t));
    }
    auto front = CreateFrameData(GetTexture(TextureId::HeroIdleFront), {1, 1}, {0, 0}, 1, 0);
    if (front.isValid_) {
        std::get<2>(k) = FaceDirection::Down;
        AddAnimation(k, Animation(front.texture_, front.frames_, front.defaultFrame_, t));
    }
    auto back = CreateFrameData(GetTexture(TextureId::HeroIdleBack), {1, 1}, {0, 0}, 1, 0);
    if (back.isValid_) {
        std::get<2>(k) = FaceDirection::Up;
        AddAnimation(k, Animation(back.texture_, back.frames_, back.defaultFrame_, t));
    }
}

void AnimationDb::InitPlayerAttack()
{
    float t = 0.1f;
    Key k = std::make_tuple(EntityType::Player, FrameType::Attack, FaceDirection::Left);

    auto side = CreateFrameData(GetTexture(TextureId::HeroAttackSide), {3, 1}, {0, 0}, 3, 0);
    if (side.isValid_) {
        std::get<2>(k) = FaceDirection::Left;
        AddAnimation(k, Animation(side.texture_, SpriteSheet::MirrorX(side.frames_), side.defaultFrame_, t));
        std::get<2>(k) = FaceDirection::Right;
        AddAnimation(k, Animation(side.texture_, side.frames_, side.defaultFrame_, t));
    }
    auto front = CreateFrameData(GetTexture(TextureId::HeroAttackFront), {3, 1}, {0, 0}, 3, 0);
    if (front.isValid_) {
        std::get<2>(k) = FaceDirection::Down;
        AddAnimation(k, Animation(front.texture_, front.frames_, front.defaultFrame_, t));
    }
    auto back = CreateFrameData(GetTexture(TextureId::HeroAttackBack), {3, 1}, {0, 0}, 3, 0);
    if (back.isValid_) {
        std::get<2>(k) = FaceDirection::Up;
        AddAnimation(k, Animation(back.texture_, back.frames_, back.defaultFrame_, t));
    }
}

void AnimationDb::InitPlayerAttackWeapon()
{
    float t = 0.1f;
    Key k = std::make_tuple(EntityType::Player, FrameType::AttackWeapon, FaceDirection::Left);

    auto side = CreateFrameData(GetTexture(TextureId::HeroAttackWeaponSide), {3, 1}, {0, 0}, 3, 0);
    if (side.isValid_) {
        std::get<2>(k) = FaceDirection::Left;
        AddAnimation(k, Animation(side.texture_, SpriteSheet::MirrorX(side.frames_), side.defaultFrame_, t));
        std::get<2>(k) = FaceDirection::Right;
        AddAnimation(k, Animation(side.texture_, side.frames_, side.defaultFrame_, t));
    }
    auto front = CreateFrameData(GetTexture(TextureId::HeroAttackWeaponFront), {3, 1}, {0, 0}, 3, 0);
    if (front.isValid_) {
        std::get<2>(k) = FaceDirection::Down;
        AddAnimation(k, Animation(front.texture_, front.frames_, front.defaultFrame_, t));
    }
    auto back = CreateFrameData(GetTexture(TextureId::HeroAttackWeaponBack), {3, 1}, {0, 0}, 3, 0);
    if (back.isValid_) {
        std::get<2>(k) = FaceDirection::Up;
        AddAnimation(k, Animation(back.texture_, back.frames_, back.defaultFrame_, t));
    }
}

void AnimationDb::InitMole()
{
    InitMoleMove();
    InitMoleIdle();
}

void AnimationDb::InitMoleMove()
{
    float t = 0.1f;
    Key k = std::make_tuple(EntityType::Mole, FrameType::Move, FaceDirection::Left);

    auto side = CreateFrameData(GetTexture(TextureId::MoleWalkSide), {6, 1}, {0, 0}, 6, 0);
    if (side.isValid_) {
        std::get<2>(k) = FaceDirection::Left;
        AddAnimation(k, Animation(side.texture_, SpriteSheet::MirrorX(side.frames_), side.defaultFrame_, t));
        std::get<2>(k) = FaceDirection::Right;
        AddAnimation(k, Animation(side.texture_, side.frames_, side.defaultFrame_, t));
    }
    auto front = CreateFrameData(GetTexture(TextureId::MoleWalkFront), {6, 1}, {0, 0}, 6, 0);
    if (front.isValid_) {
        std::get<2>(k) = FaceDirection::Down;
        AddAnimation(k, Animation(front.texture_, front.frames_, front.defaultFrame_, t));
    }
    auto back = CreateFrameData(GetTexture(TextureId::MoleWalkBack), {6, 1}, {0, 0}, 6, 0);
    if (back.isValid_) {
        std::get<2>(k) = FaceDirection::Up;
        AddAnimation(k, Animation(back.texture_, back.frames_, back.defaultFrame_, t));
    }
}

void AnimationDb::InitMoleIdle()
{
    float t = 0.1f;
    Key k = std::make_tuple(EntityType::Mole, FrameType::Idle, FaceDirection::Left);

    auto side = CreateFrameData(GetTexture(TextureId::MoleIdleSide), {1, 1}, {0, 0}, 1, 0);
    if (side.isValid_) {
        std::get<2>(k) = FaceDirection::Left;
        AddAnimation(k, Animation(side.texture_, SpriteSheet::MirrorX(side.frames_), side.defaultFrame_, t));
        std::get<2>(k) = FaceDirection::Right;
        AddAnimation(k, Animation(side.texture_, side.frames_, side.defaultFrame_, t));
    }
    auto front = CreateFrameData(GetTexture(TextureId::MoleIdleFront), {1, 1}, {0, 0}, 1, 0);
    if (front.isValid_) {
        std::get<2>(k) = FaceDirection::Down;
        AddAnimation(k, Animation(front.texture_, front.frames_, front.defaultFrame_, t));
    }
    auto back = CreateFrameData(GetTexture(TextureId::MoleIdleBack), {1, 1}, {0, 0}, 1, 0);
    if (back.isValid_) {
        std::get<2>(k) = FaceDirection::Up;
        AddAnimation(k, Animation(back.texture_, back.frames_, back.defaultFrame_, t));
    }
}

void AnimationDb::AddAnimation(Key k, const Animation& animation)
{
    map_[k] = animation;
}

const sf::Texture* AnimationDb::GetTexture(const std::string& name) const
{
    return textureManager_.Get(name);
}

}  // namespace Entity

}  // namespace FA
