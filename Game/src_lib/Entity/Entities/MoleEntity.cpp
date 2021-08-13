/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Animation/AnimationComponent.h"
#include "Entity/Components/Sprite/SpriteComponent.h"
#include "Entity/ConfigurationBuilder.h"
#include "Entity/ConfigurationData.h"
#include "Entity/TextureId.h"
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

MoleEntity::MoleEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : BasicEntity(id, messageBus, textureManager)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(const ConfigurationData& configurationData)
{
    ConfigurationBuilder builder(configurationData.position_, configurationData.scale_, configurationData.faceDir_);
    builder.AddMovement(configurationData.velocity_);
    builder.AddSprite(CreateAnimation());
    auto c = builder.Build();

    InitStateData(c);
}

AnimationComponent MoleEntity::CreateAnimation() const
{
    AnimationComponent animation;
    float t = 0.1f;

    /* Move animations */
    auto wside = CreateFrameData(GetTexture(TextureId::MoleWalkSide), {6, 1}, {0, 0}, 6, 0);
    if (wside.isValid_) {
        animation.AddAnimation(FrameType::Move, FaceDirection::Left,
                               Animation(wside.texture_, SpriteSheet::MirrorX(wside.frames_), wside.defaultFrame_, t));
        animation.AddAnimation(FrameType::Move, FaceDirection::Right,
                               Animation(wside.texture_, wside.frames_, wside.defaultFrame_, t));
    }
    auto wfront = CreateFrameData(GetTexture(TextureId::MoleWalkFront), {6, 1}, {0, 0}, 6, 0);
    if (wfront.isValid_) {
        animation.AddAnimation(FrameType::Move, FaceDirection::Down,
                               Animation(wfront.texture_, wfront.frames_, wfront.defaultFrame_, t));
    }
    auto wback = CreateFrameData(GetTexture(TextureId::MoleWalkBack), {6, 1}, {0, 0}, 6, 0);
    if (wback.isValid_) {
        animation.AddAnimation(FrameType::Move, FaceDirection::Up,
                               Animation(wback.texture_, wback.frames_, wback.defaultFrame_, t));
    }

    /* Idle animations */
    auto iside = CreateFrameData(GetTexture(TextureId::MoleIdleSide), {1, 1}, {0, 0}, 1, 0);
    if (wside.isValid_) {
        animation.AddAnimation(FrameType::Idle, FaceDirection::Left,
                               Animation(iside.texture_, SpriteSheet::MirrorX(iside.frames_), iside.defaultFrame_, t));
        animation.AddAnimation(FrameType::Idle, FaceDirection::Right,
                               Animation(iside.texture_, iside.frames_, iside.defaultFrame_, t));
    }
    auto ifront = CreateFrameData(GetTexture(TextureId::MoleIdleFront), {1, 1}, {0, 0}, 1, 0);
    if (ifront.isValid_) {
        animation.AddAnimation(FrameType::Idle, FaceDirection::Down,
                               Animation(ifront.texture_, ifront.frames_, ifront.defaultFrame_, t));
    }
    auto iback = CreateFrameData(GetTexture(TextureId::MoleIdleBack), {1, 1}, {0, 0}, 1, 0);
    if (iback.isValid_) {
        animation.AddAnimation(FrameType::Idle, FaceDirection::Up,
                               Animation(iback.texture_, iback.frames_, iback.defaultFrame_, t));
    }

    return animation;
}

}  // namespace Entity

}  // namespace FA
