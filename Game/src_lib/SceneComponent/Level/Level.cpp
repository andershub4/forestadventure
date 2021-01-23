/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Level.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Entity.h"
#include "Game/Layer.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"
#include "Sprite/SpriteSheet.h"

namespace FA {

Level::Level(MessageBus& messageBus, TextureManager& textureManager)
    : messageBus_(messageBus)
    , animationFactory_(0.1f)
{
    RegisterAnimationInfo(textureManager);
    entity_ = std::make_unique<Entity>(messageBus, animationFactory_);
}

Level::~Level() = default;

void Level::DrawTo(Layer& layer)
{
    layer.Clear();
    entity_->DrawTo(layer);
    layer.Display();
}

void Level::Update(float deltaTime)
{
    entity_->Update(deltaTime);
}

void Level::RegisterAnimationInfo(TextureManager& textureManager)
{
    auto textureWalkSide =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-side.png");
    if (textureWalkSide != nullptr) {
        SpriteSheet spriteSheet("heroWalkSide", textureWalkSide, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Move, FaceDirection::Left, f.texture_, f.frames_,
                                                f.defaultFrame_, true);
        animationFactory_.RegisterAnimationInfo(FrameType::Move, FaceDirection::Right, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureWalkFront =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-front.png");
    if (textureWalkFront != nullptr) {
        SpriteSheet spriteSheet("heroWalkFront", textureWalkFront, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Move, FaceDirection::Down, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureWalkBack =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-back-walk.png");
    if (textureWalkBack != nullptr) {
        SpriteSheet spriteSheet("heroWalkBack", textureWalkBack, {6, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 6, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Move, FaceDirection::Up, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }

    auto textureAttackSide =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-side.png");
    if (textureAttackSide != nullptr) {
        SpriteSheet spriteSheet("heroAttackSide", textureAttackSide, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Left, f.texture_, f.frames_,
                                                f.defaultFrame_, true);
        animationFactory_.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Right, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureAttackFront =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-front.png");
    if (textureAttackFront != nullptr) {
        SpriteSheet spriteSheet("heroAttackFront", textureAttackFront, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Down, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureAttackBack =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-back.png");
    if (textureAttackBack != nullptr) {
        SpriteSheet spriteSheet("heroAttackBack", textureAttackBack, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Attack, FaceDirection::Up, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }

    auto textureIdleSide =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-side.png");
    if (textureIdleSide != nullptr) {
        SpriteSheet spriteSheet("heroIdleSide", textureIdleSide, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Left, f.texture_, f.frames_,
                                                f.defaultFrame_, true);
        animationFactory_.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Right, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureIdleFront =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-front.png");
    if (textureIdleFront != nullptr) {
        SpriteSheet spriteSheet("heroIdleFront", textureIdleFront, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Down, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureIdleBack =
        textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-back.png");
    if (textureIdleBack != nullptr) {
        SpriteSheet spriteSheet("heroIdleBack", textureIdleBack, {1, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 1, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::Idle, FaceDirection::Up, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
}

}  // namespace FA
