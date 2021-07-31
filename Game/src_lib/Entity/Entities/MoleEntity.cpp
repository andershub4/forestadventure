/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoleEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Components/Sprite/Sprite.h"
#include "Entity/Configuration.h"
#include "Entity/TextureId.h"
#include "Message/MessageBus.h"
#include "Resource/SpriteSheet.h"

namespace FA {

namespace Entity {

MoleEntity::MoleEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : BasicEntity(id, messageBus, textureManager)
{}

MoleEntity::~MoleEntity() = default;

void MoleEntity::OnCreate(const Configuration& configuration)
{
    AnimationDB db(0.1f);

    auto textureWalkSide = GetTexture(TextureId::MoleWalkSide);
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("moleWalkSide", textureWalkSide, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        auto mf = SpriteSheet::MirrorX(f);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, mf.texture_, mf.frames_, mf.defaultFrame_);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkFront = GetTexture(TextureId::MoleWalkFront);
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("moleWalkFront", textureWalkFront, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureWalkBack = GetTexture(TextureId::MoleWalkBack);
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("moleWalkBack", textureWalkBack, {6, 1});
        auto f = spriteSheet.Scan({0, 0}, 6, 0);
        db.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    auto textureIdleSide = GetTexture(TextureId::MoleIdleSide);
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("moleIdleSide", textureIdleSide, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        auto mf = SpriteSheet::MirrorX(f);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, mf.texture_, mf.frames_, mf.defaultFrame_);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleFront = GetTexture(TextureId::MoleIdleFront);
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("moleIdleFront", textureIdleFront, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_, f.defaultFrame_);
    }
    auto textureIdleBack = GetTexture(TextureId::MoleIdleBack);
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("moleIdleBack", textureIdleBack, {1, 1});
        auto f = spriteSheet.Scan({0, 0}, 1, 0);
        db.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_, f.defaultFrame_);
    }

    InitStateData(configuration, db);
}

}  // namespace Entity

}  // namespace FA
