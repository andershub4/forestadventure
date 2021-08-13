/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Animation/AnimationComponent.h"
#include "Entity/Components/Sprite/SpriteComponent.h"
#include "Entity/ConfigurationData.h"
#include "Entity/TextureId.h"
#include "Message/MessageBus.h"
#include "Resource/SpriteSheet.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : BasicEntity(id, messageBus, textureManager)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(const ConfigurationData& configurationData)
{
    AnimationComponent animation;
    float t = 0.1f;

    auto textureWalkSide = GetTexture(TextureId::MoleWalkSide);
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("moleWalkSide", textureWalkSide, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        auto mf = SpriteSheet::MirrorX(f);
        auto a = Animation(f.texture_, f.frames_, f.defaultFrame_, t);
        auto ma = Animation(mf.texture_, mf.frames_, mf.defaultFrame_, t);
        animation.AddAnimation(FrameType::Move, FaceDirection::Left, ma);
        animation.AddAnimation(FrameType::Move, FaceDirection::Right, a);
    }
    auto textureWalkFront = GetTexture(TextureId::MoleWalkFront);
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("moleWalkFront", textureWalkFront, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        auto a = Animation(f.texture_, f.frames_, f.defaultFrame_, t);
        animation.AddAnimation(FrameType::Move, FaceDirection::Down, a);
    }
    auto textureWalkBack = GetTexture(TextureId::MoleWalkBack);
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("moleWalkBack", textureWalkBack, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        auto a = Animation(f.texture_, f.frames_, f.defaultFrame_, t);
        animation.AddAnimation(FrameType::Move, FaceDirection::Up, a);
    }

    auto textureIdleSide = GetTexture(TextureId::MoleIdleSide);
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("moleIdleSide", textureIdleSide, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        auto mf = SpriteSheet::MirrorX(f);
        auto a = Animation(f.texture_, f.frames_, f.defaultFrame_, t);
        auto ma = Animation(mf.texture_, mf.frames_, mf.defaultFrame_, t);
        animation.AddAnimation(FrameType::Idle, FaceDirection::Left, ma);
        animation.AddAnimation(FrameType::Idle, FaceDirection::Right, a);
    }
    auto textureIdleFront = GetTexture(TextureId::MoleIdleFront);
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("moleIdleFront", textureIdleFront, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        auto a = Animation(f.texture_, f.frames_, f.defaultFrame_, t);
        animation.AddAnimation(FrameType::Idle, FaceDirection::Down, a);
    }
    auto textureIdleBack = GetTexture(TextureId::MoleIdleBack);
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("moleIdleBack", textureIdleBack, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        auto a = Animation(f.texture_, f.frames_, f.defaultFrame_, t);
        animation.AddAnimation(FrameType::Idle, FaceDirection::Up, a);
    }

    InitStateData(configurationData, animation);
}

}  // namespace Entity

}  // namespace FA
