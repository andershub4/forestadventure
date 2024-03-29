/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "PreAlphaLayer.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Folder.h"
#include "Logging.h"
#include "Message/MessageBus.h"
#include "Version.h"

namespace FA {

namespace Scene {

PreAlphaLayer::PreAlphaLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect)
    : BasicLayer(messageBus, rect)
{}

PreAlphaLayer::~PreAlphaLayer() = default;

void PreAlphaLayer::OnLoad()
{
    std::string path = Util::GetAssetsPath() + "/font/intuitive/intuitive.ttf";
    if (!font_.loadFromFile(path)) {
        LOG_ERROR("Could not load %s", DUMP(path));
    }
}

void PreAlphaLayer::OnCreate()
{
    versionText_.setFont(font_);
    std::string s = "Pre-alpha version " + std::string(FA_APP_VERSION) + " [Press<ESC> to Exit]";
    versionText_.setString(s);
    versionText_.setCharacterSize(24);
    versionText_.setFillColor(sf::Color::White);
    auto bounds1 = versionText_.getGlobalBounds();
    auto w1 = bounds1.width;
    sf::Vector2f versionTextPos(layerTexture_.getSize().x / 2.0f - w1 / 2.0f, 0.0f);
    versionText_.setPosition(versionTextPos);
}

void PreAlphaLayer::Draw()
{
    layerTexture_.draw(versionText_);
}

void PreAlphaLayer::Update(float deltaTime)
{}

}  // namespace Scene

}  // namespace FA
