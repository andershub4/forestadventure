/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Animation/AnimationFactory.h"
#include "Constant/Screen.h"
#include "Effect/BasicEffect.h"
#include "Entity/Components/Sprite/AnimatedSprite.h"
#include "Entity/Components/Sprite/StaticSprite.h"
#include "Entity/Entities/MoleEntity.h"
#include "Entity/Entities/PlayerEntity.h"
#include "Entity/Entities/StaticEntity.h"
#include "Enum/AnimationId.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"
#include "Scene/Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

LevelComponent::LevelComponent(MessageBus& messageBus, TextureManager& textureManager)
    : BasicComponent(messageBus)
    , animationManager_(textureManager)
    , tileMap_()
    , view_({constant::Screen::centerX_f, constant::Screen::centerY_f},
            {constant::Screen::width_f, constant::Screen::height_f})
{
    animationManager_.RegisterFactories();

    auto animationFactory = animationManager_.GetFactory(AnimationId::Player);
    auto moleAnimationFactory = animationManager_.GetFactory(AnimationId::Mole);

    auto sprite = std::make_unique<Entity::AnimatedSprite>(64, sf::Vector2u(0, 0), animationFactory);
    auto moleSprite = std::make_unique<Entity::AnimatedSprite>(48, sf::Vector2u(8 * 32, 8 * 32), moleAnimationFactory);

    auto textureStone = textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/environment/tileset.png");
    auto stoneSprite = std::make_unique<Entity::StaticSprite>(32, sf::Vector2u(8 * 64, 8 * 10), textureStone,
                                                              sf::IntRect(272, 480, 16, 16));

    entity_ = std::make_unique<Entity::PlayerEntity>(messageBus, std::move(sprite), FaceDirection::Down, 120.0f);
    entity_->OnCreate();

    moleEntity_ = std::make_unique<Entity::MoleEntity>(messageBus, std::move(moleSprite), FaceDirection::Down, 120.0f);
    moleEntity_->OnCreate();

    stoneEntity_ = std::make_unique<Entity::StaticEntity>(messageBus, std::move(stoneSprite));
    stoneEntity_->OnCreate();

    auto textureTileSet = textureManager.GetTexture("assets/tiny-RPG-forest-files/PNG/environment/tileset.png");
    if (textureTileSet != nullptr) {
        tileMap_.Load(textureTileSet);
    }
}

LevelComponent::~LevelComponent()
{
    entity_->OnDestroy();
    moleEntity_->OnDestroy();
}

void LevelComponent::Draw()
{
    tileMap_.DrawTo(renderTexture_);
    entity_->DrawTo(renderTexture_);
    moleEntity_->DrawTo(renderTexture_);
    stoneEntity_->DrawTo(renderTexture_);
    if (effect_) effect_->DrawTo(renderTexture_);
}

void LevelComponent::Update(float deltaTime)
{
    entity_->Update(deltaTime);
    moleEntity_->Update(deltaTime);
    stoneEntity_->Update(deltaTime);
    if (effect_) effect_->Update(deltaTime);

    auto p = entity_->GetPosition();
    auto viewPosition = CalcViewPosition(p);
    view_.setCenter(viewPosition);
    renderTexture_.setView(view_);
}

void LevelComponent::EnableInput(bool enable)
{
    entity_->EnableInput(enable);
    moleEntity_->EnableInput(enable);
    stoneEntity_->EnableInput(enable);
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

}  // namespace Scene

}  // namespace FA
