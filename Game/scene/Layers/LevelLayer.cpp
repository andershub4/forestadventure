/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "LevelLayer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Effect/BasicEffect.h"
#include "Level/Level.h"
#include "Transitions/BasicTransition.h"

namespace FA {

namespace Scene {

LevelLayer::LevelLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect, Shared::TextureManager& textureManager)
    : BasicLayer(messageBus, rect)
    , messageBus_(messageBus)
    , textureManager_(textureManager)
{
    auto viewSize = layerTexture_.getSize();
    level_ = std::make_unique<Level>(messageBus_, textureManager_, viewSize);
}

LevelLayer::~LevelLayer() = default;

void LevelLayer::OnLoad()
{
    level_->Load("level.tmx");
}

void LevelLayer::OnCreate()
{
    level_->Create();
}

void LevelLayer::Draw()
{
    auto view = level_->GetView();
    layerTexture_.setView(view);
    level_->Draw(layerTexture_);  // When drawing, the view must already have been set
    if (effect_) effect_->DrawTo(layerTexture_);
}

void LevelLayer::Update(float deltaTime)
{
    level_->Update(deltaTime);
    if (effect_) effect_->Update(deltaTime);
}

void LevelLayer::EnterTransition(const BasicTransition& transition)
{
    sf::Vector2f layerPos = layerTexture_.mapPixelToCoords({0, 0});
    sf::Vector2f layerSize = static_cast<sf::Vector2f>(layerTexture_.getSize());
    effect_ = transition.CreateEffect(layerPos, layerSize);
}

void LevelLayer::ExitTransition(const BasicTransition& transition)
{
    effect_.reset();
}

}  // namespace Scene

}  // namespace FA
