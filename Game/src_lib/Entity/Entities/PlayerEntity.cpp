/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PlayerEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/ConfigurationBuilder.h"
#include "Entity/ConfigurationData.h"
#include "Entity/TextureId.h"
#include "Enum/KeyboardKey.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"
#include "Resource/SpriteSheet.h"

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

PlayerEntity::PlayerEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : BasicEntity(id, messageBus, textureManager)
{}

PlayerEntity::~PlayerEntity() = default;

void PlayerEntity::OnCreate(const ConfigurationData& configurationData)
{
    ConfigurationBuilder builder(configurationData.position_, configurationData.scale_, configurationData.faceDir_);
    builder.AddMovement(configurationData.velocity_);
    builder.AddSprite(CreateAnimation());
    auto c = builder.Build();

    InitStateData(std::move(c));
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

AnimationComponent PlayerEntity::CreateAnimation() const
{
    AnimationComponent animation;
    float t = 0.1f;

    /* Move animations */
    auto wside = CreateFrameData(GetTexture(TextureId::HeroWalkSide), {6, 1}, {0, 0}, 6, 0);
    if (wside.isValid_) {
        animation.AddAnimation(FrameType::Move, FaceDirection::Left,
                               Animation(wside.texture_, SpriteSheet::MirrorX(wside.frames_), wside.defaultFrame_, t));
        animation.AddAnimation(FrameType::Move, FaceDirection::Right,
                               Animation(wside.texture_, wside.frames_, wside.defaultFrame_, t));
    }
    auto wfront = CreateFrameData(GetTexture(TextureId::HeroWalkFront), {6, 1}, {0, 0}, 6, 0);
    if (wfront.isValid_) {
        animation.AddAnimation(FrameType::Move, FaceDirection::Down,
                               Animation(wfront.texture_, wfront.frames_, wfront.defaultFrame_, t));
    }
    auto wback = CreateFrameData(GetTexture(TextureId::HeroWalkBack), {6, 1}, {0, 0}, 6, 0);
    if (wback.isValid_) {
        animation.AddAnimation(FrameType::Move, FaceDirection::Up,
                               Animation(wback.texture_, wback.frames_, wback.defaultFrame_, t));
    }

    /* Attack animations */
    auto aside = CreateFrameData(GetTexture(TextureId::HeroAttackSide), {3, 1}, {0, 0}, 3, 0);
    if (aside.isValid_) {
        animation.AddAnimation(FrameType::Attack, FaceDirection::Left,
                               Animation(aside.texture_, SpriteSheet::MirrorX(aside.frames_), aside.defaultFrame_, t));
        animation.AddAnimation(FrameType::Attack, FaceDirection::Right,
                               Animation(aside.texture_, aside.frames_, aside.defaultFrame_, t));
    }
    auto afront = CreateFrameData(GetTexture(TextureId::HeroAttackFront), {3, 1}, {0, 0}, 3, 0);
    if (afront.isValid_) {
        animation.AddAnimation(FrameType::Attack, FaceDirection::Down,
                               Animation(afront.texture_, afront.frames_, afront.defaultFrame_, t));
    }
    auto aback = CreateFrameData(GetTexture(TextureId::HeroAttackBack), {3, 1}, {0, 0}, 3, 0);
    if (aback.isValid_) {
        animation.AddAnimation(FrameType::Attack, FaceDirection::Up,
                               Animation(aback.texture_, aback.frames_, aback.defaultFrame_, t));
    }

    /* Attack weapon animations */
    auto awside = CreateFrameData(GetTexture(TextureId::HeroAttackWeaponSide), {3, 1}, {0, 0}, 3, 0);
    if (awside.isValid_) {
        animation.AddAnimation(
            FrameType::AttackWeapon, FaceDirection::Left,
            Animation(awside.texture_, SpriteSheet::MirrorX(awside.frames_), awside.defaultFrame_, t));
        animation.AddAnimation(FrameType::AttackWeapon, FaceDirection::Right,
                               Animation(awside.texture_, awside.frames_, awside.defaultFrame_, t));
    }
    auto awfront = CreateFrameData(GetTexture(TextureId::HeroAttackWeaponFront), {3, 1}, {0, 0}, 3, 0);
    if (awfront.isValid_) {
        animation.AddAnimation(FrameType::AttackWeapon, FaceDirection::Down,
                               Animation(awfront.texture_, awfront.frames_, awfront.defaultFrame_, t));
    }
    auto awback = CreateFrameData(GetTexture(TextureId::HeroAttackWeaponBack), {3, 1}, {0, 0}, 3, 0);
    if (awback.isValid_) {
        animation.AddAnimation(FrameType::AttackWeapon, FaceDirection::Up,
                               Animation(awback.texture_, awback.frames_, awback.defaultFrame_, t));
    }

    /* Idle animations */
    auto iside = CreateFrameData(GetTexture(TextureId::HeroIdleSide), {1, 1}, {0, 0}, 1, 0);
    if (iside.isValid_) {
        animation.AddAnimation(FrameType::Idle, FaceDirection::Left,
                               Animation(iside.texture_, SpriteSheet::MirrorX(iside.frames_), iside.defaultFrame_, t));
        animation.AddAnimation(FrameType::Idle, FaceDirection::Right,
                               Animation(iside.texture_, iside.frames_, iside.defaultFrame_, t));
    }
    auto ifront = CreateFrameData(GetTexture(TextureId::HeroIdleFront), {1, 1}, {0, 0}, 1, 0);
    if (ifront.isValid_) {
        animation.AddAnimation(FrameType::Idle, FaceDirection::Down,
                               Animation(ifront.texture_, ifront.frames_, ifront.defaultFrame_, t));
    }
    auto iback = CreateFrameData(GetTexture(TextureId::HeroIdleBack), {1, 1}, {0, 0}, 1, 0);
    if (iback.isValid_) {
        animation.AddAnimation(FrameType::Idle, FaceDirection::Up,
                               Animation(iback.texture_, iback.frames_, iback.defaultFrame_, t));
    }

    return animation;
}

}  // namespace Entity

}  // namespace FA
