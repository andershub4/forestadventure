/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/SpriteComponent.h"
#include "Entity/Configuration.h"
#include "Entity/TextureId.h"
#include "Enum/KeyboardKey.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"
#include "Resource/SpriteSheet.h"

namespace FA {

namespace Entity {

PlayerEntity::PlayerEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : BasicEntity(id, messageBus, textureManager)
{}

PlayerEntity::~PlayerEntity() = default;

void PlayerEntity::OnCreate(const Configuration& configuration)
{
    AnimationDB db(0.1f);

    auto textureWalkSide = GetTexture(TextureId::HeroWalkSide);
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("heroWalkSide", textureWalkSide, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        auto mf = SpriteSheet::MirrorX(f);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, mf.texture_, mf.frames_, mf.defaultFrame_);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront = GetTexture(TextureId::HeroWalkFront);
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("heroWalkFront", textureWalkFront, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack = GetTexture(TextureId::HeroWalkBack);
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("heroWalkBack", textureWalkBack, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureAttackSide = GetTexture(TextureId::HeroAttackSide);
    if (textureAttackSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackSide", textureAttackSide, {3, 1});
        auto f = spriteSheet.Scan({0, 0}, 3, 0);
        auto mf = SpriteSheet::MirrorX(f);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Left, mf.texture_, mf.frames_, mf.defaultFrame_);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackFront = GetTexture(TextureId::HeroAttackFront);
    if (textureAttackFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackFront", textureAttackFront, {3, 1});
        auto f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackBack = GetTexture(TextureId::HeroAttackBack);
    if (textureAttackBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackBack", textureAttackBack, {3, 1});
        auto f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureAttackWeaponSide = GetTexture(TextureId::HeroAttackWeaponSide);
    if (textureAttackWeaponSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponSide", textureAttackWeaponSide, {3, 1});
        auto f = spriteSheet.Scan({0, 0}, 3, 0);
        auto mf = SpriteSheet::MirrorX(f);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Left, mf.texture_, mf.frames_,
                                 mf.defaultFrame_);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackWeaponFront = GetTexture(TextureId::HeroAttackWeaponFront);
    if (textureAttackWeaponFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponFront", textureAttackWeaponFront, {3, 1});
        auto f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureAttackWeaponBack = GetTexture(TextureId::HeroAttackWeaponBack);
    if (textureAttackWeaponBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponBack", textureAttackWeaponBack, {3, 1});
        auto f = spriteSheet.Scan({0, 0}, 3, 0);
        db.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureIdleSide = GetTexture(TextureId::HeroIdleSide);
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("heroIdleSide", textureIdleSide, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        auto mf = SpriteSheet::MirrorX(f);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, mf.texture_, mf.frames_, mf.defaultFrame_);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront = GetTexture(TextureId::HeroIdleFront);
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("heroIdleFront", textureIdleFront, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack = GetTexture(TextureId::HeroIdleBack);
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("heroIdleBack", textureIdleBack, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    InitStateData(configuration, db);
    Subscribe({MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void PlayerEntity::OnDestroy()
{
    Unsubscribe({MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void PlayerEntity::OnIsKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::Right) {
        StartMove(MoveDirection::Right, FaceDirection::Right);
    }
    else if (key == Keyboard::Key::Left) {
        StartMove(MoveDirection::Left, FaceDirection::Left);
    }
    else if (key == Keyboard::Key::Up) {
        StartMove(MoveDirection::Up, FaceDirection::Up);
    }
    else if (key == Keyboard::Key::Down) {
        StartMove(MoveDirection::Down, FaceDirection::Down);
    }
}

void PlayerEntity::OnIsKeyReleased(Keyboard::Key key)
{
    StopMove();
}

void PlayerEntity::OnKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::RControl) {
        Attack();
    }
    else if (key == Keyboard::Key::Space) {
        AttackWeapon();
    }
}

}  // namespace Entity

}  // namespace FA
