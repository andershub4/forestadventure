/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IntroComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Folder.h"
#include "Logging.h"
#include "Message/MessageBus.h"
#include "Scene/Layer.h"

namespace FA {

namespace Scene {

IntroComponent::IntroComponent(MessageBus& messageBus, const Layer& layer)
    : BasicComponent(messageBus, layer)
{
    std::string path = GetAssetsPath() + "/font/intuitive/intuitive.ttf";
    if (!font_.loadFromFile(path)) {
        LOG_ERROR("Could not load ", path);
    }

    introText_.setFont(font_);
    introText_.setString("<ForestAdventure>");
    introText_.setCharacterSize(64);
    introText_.setFillColor(sf::Color::White);
    auto bounds1 = introText_.getGlobalBounds();
    auto w1 = bounds1.width;
    sf::Vector2f introTextPos(layerTexture_.getSize().x / 2.0f - w1 / 2, 300.0f);
    introText_.setPosition(introTextPos);

    pressText_.setFont(font_);
    pressText_.setString("Press <ENTER> to start play");
    pressText_.setCharacterSize(24);
    pressText_.setFillColor(sf::Color::White);
    auto bounds2 = pressText_.getGlobalBounds();
    auto w2 = bounds2.width;
    sf::Vector2f pressTextPos(layerTexture_.getSize().x / 2.0f - w2 / 2, 400.0f);
    pressText_.setPosition(pressTextPos);
}

IntroComponent::~IntroComponent() = default;

void IntroComponent::Draw()
{
    layerTexture_.draw(introText_);
    layerTexture_.draw(pressText_);
}

void IntroComponent::Update(float deltaTime)
{}

}  // namespace Scene

}  // namespace FA
