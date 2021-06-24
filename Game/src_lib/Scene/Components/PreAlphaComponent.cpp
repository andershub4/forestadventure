/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PreAlphaComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Folder.h"
#include "Logging.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Scene {

PreAlphaComponent::PreAlphaComponent(MessageBus& messageBus)
    : BasicComponent(messageBus)
{
    std::string path = GetAssetsPath() + "/font/intuitive/intuitive.ttf";
    if (!font_.loadFromFile(path)) {
        LOG_ERROR("Could not load intuitive");
    }

    versionText_.setFont(font_);
    versionText_.setString("Pre-alpha version [Press <ESC> to Exit]");
    versionText_.setCharacterSize(24);
    versionText_.setFillColor(sf::Color::White);
    auto bounds1 = versionText_.getGlobalBounds();
    auto w1 = bounds1.width;
    sf::Vector2f introTextPos(constant::Screen::width_f / 2 - w1 / 2, 0.0f);
    versionText_.setPosition(introTextPos);
}

PreAlphaComponent::~PreAlphaComponent() = default;

void PreAlphaComponent::Draw()
{
    layerTexture_.draw(versionText_);
}

void PreAlphaComponent::Update(float deltaTime)
{}

}  // namespace Scene

}  // namespace FA
