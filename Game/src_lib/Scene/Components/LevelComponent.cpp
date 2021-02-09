/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Effect/BasicEffect.h"
#include "Entity/Entities/PlayerEntity.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"
#include "Scene/Transitions/BasicTransition.h"
#include "Sprite/SpriteSheet.h"

namespace FA {

namespace Scene {

LevelComponent::LevelComponent(MessageBus& messageBus, TextureManager& textureManager)
    : BasicComponent(messageBus)
    , animationFactory_(0.1f)
    , tileMap_()
    , view_({constant::Screen::centerX_f, constant::Screen::centerY_f},
            {constant::Screen::width_f, constant::Screen::height_f})
{
    RegisterAnimationInfo(textureManager);
    entity_ = std::make_unique<Entity::PlayerEntity>(messageBus, sf::Vector2u(0, 0), 64, FaceDirection::Down,
                                                     MoveDirection::Down, animationFactory_, 120.0f);
    entity_->OnCreate();

    auto textureTileSet = textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/environment/tileset.png");
    if (textureTileSet != nullptr) {
        tileMap_.Load(textureTileSet);
    }
}

LevelComponent::~LevelComponent()
{
    entity_->OnDestroy();
}

void LevelComponent::Draw()
{
    tileMap_.DrawTo(renderTexture_);
    entity_->DrawTo(renderTexture_);
    if (effect_) effect_->DrawTo(renderTexture_);
}

void LevelComponent::Update(float deltaTime)
{
    entity_->Update(deltaTime);
    if (effect_) effect_->Update(deltaTime);

    auto p = entity_->GetPosition();
    auto viewPosition = CalcViewPosition(p);
    view_.setCenter(viewPosition);
    renderTexture_.setView(view_);
}

void LevelComponent::EnableInput(bool enable)
{
    entity_->EnableInput(enable);
}

void LevelComponent::EnterTransition(const BasicTransition& transition)
{
    auto size = view_.getSize();
    auto position = view_.getCenter();
    position.x = position.x - size.x / 2;
    position.y = position.y - size.y / 2;

    effect_ = transition.CreateEffect(position, size);
}

void LevelComponent::ExitTransition(const BasicTransition& transition)
{
    effect_.reset();
}

sf::Vector2f LevelComponent::CalcViewPosition(const sf::Vector2f& position) const
{
    auto viewPosition = sf::Vector2f(position.x, position.y);

    if (position.x <= constant::Screen::centerX_f) {
        viewPosition.x = constant::Screen::centerX_f;
    }
    else if (position.x >= (tileMap_.GetSize().x - constant::Screen::centerX_f)) {
        viewPosition.x = tileMap_.GetSize().x - constant::Screen::centerX_f;
    }

    if (position.y <= constant::Screen::centerY_f) {
        viewPosition.y = constant::Screen::centerY_f;
    }
    else if (position.y >= (tileMap_.GetSize().y - constant::Screen::centerY_f)) {
        viewPosition.y = tileMap_.GetSize().y - constant::Screen::centerY_f;
    }

    return viewPosition;
}

void LevelComponent::RegisterAnimationInfo(TextureManager& textureManager)
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

    auto textureAttackSideWeapon = textureManager.GetTexture(
        "assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack-weapon/hero-attack-side-weapon.png");
    if (textureAttackSideWeapon != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponSide", textureAttackSideWeapon, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Left, f.texture_, f.frames_,
                                                f.defaultFrame_, true);
        animationFactory_.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Right, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureAttackFrontWeapon = textureManager.GetTexture(
        "assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack-weapon/hero-attack-front-weapon.png");
    if (textureAttackFrontWeapon != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponFront", textureAttackFrontWeapon, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Down, f.texture_, f.frames_,
                                                f.defaultFrame_);
    }
    auto textureAttackBackWeapon = textureManager.GetTexture(
        "assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack-weapon/hero-attack-back-weapon.png");
    if (textureAttackBackWeapon != nullptr) {
        SpriteSheet spriteSheet("heroAttackWeaponBack", textureAttackBackWeapon, {3, 1});
        SpriteSheet::FrameData f = spriteSheet.Scan({0, 0}, 3, 0);
        animationFactory_.RegisterAnimationInfo(FrameType::AttackWeapon, FaceDirection::Up, f.texture_, f.frames_,
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

}  // namespace Scene

}  // namespace FA
