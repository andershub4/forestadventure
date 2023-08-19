/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "HelperLayer.h"

#include <cmath>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Folder.h"
#include "Logging.h"
#include "Message/BroadcastMessage/EntityCreatedMessage.h"
#include "Message/BroadcastMessage/EntityDestroyedMessage.h"
#include "Message/MessageBus.h"
#include "Message/MessageType.h"

namespace FA {

namespace Scene {

HelperLayer::HelperLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect, const std::string& sceneName)
    : BasicLayer(messageBus, rect)
    , sceneName_(sceneName)
{}

HelperLayer::~HelperLayer() = default;

void HelperLayer::OnLoad()
{
    std::string path = GetAssetsPath() + "/font/cello-sans/hinted-CelloSans-Medium.ttf";
    if (!font_.loadFromFile(path)) {
        LOG_ERROR("Could not load %s", DUMP(path));
    }
}

void HelperLayer::OnCreate()
{
    sceneText_.setFont(font_);
    sceneText_.setString(sceneName_);
    sceneText_.setCharacterSize(24);
    sceneText_.setFillColor(sf::Color::White);
    sf::Vector2f sceneTextPos(0.0f, 0.0f);
    sceneText_.setPosition(sceneTextPos);

    fpsText_.setFont(font_);
    fpsText_.setString("Fps:");
    fpsText_.setCharacterSize(24);
    fpsText_.setFillColor(sf::Color::White);
    sf::Vector2f fpsTextPos(1170.0f, 0.0f);
    fpsText_.setPosition(fpsTextPos);

    fpsNumberText_.setFont(font_);
    fpsNumberText_.setString("-");
    fpsNumberText_.setCharacterSize(24);
    fpsNumberText_.setFillColor(sf::Color::White);
    sf::Vector2f fpsNumberTextPos(1220.0f, 0.0f);
    fpsNumberText_.setPosition(fpsNumberTextPos);

    nEntitiesText_.setFont(font_);
    nEntitiesText_.setString("Entities count:");
    nEntitiesText_.setCharacterSize(24);
    nEntitiesText_.setFillColor(sf::Color::White);
    sf::Vector2f nEntitiesTextPos(0.0f, 50.0f);
    nEntitiesText_.setPosition(nEntitiesTextPos);

    nEntitiesCountText_.setFont(font_);
    nEntitiesCountText_.setString("0");
    nEntitiesCountText_.setCharacterSize(24);
    nEntitiesCountText_.setFillColor(sf::Color::White);
    sf::Vector2f nEntitiesCountTextPos(180.0f, 50.0f);
    nEntitiesCountText_.setPosition(nEntitiesCountTextPos);

    dotShape_.setSize(sf::Vector2f(1.0, 1.0));
    dotShape_.setPosition(layerTexture_.getSize().x / 2.0f, layerTexture_.getSize().y / 2.0f);
}

void HelperLayer::SubscribeMessages()
{
    Subscribe({Shared::MessageType::EntityInitialized, Shared::MessageType::EntityDestroyed});
}

void HelperLayer::UnsubscribeMessages()
{
    Unsubscribe({Shared::MessageType::EntityInitialized, Shared::MessageType::EntityDestroyed});
}

void HelperLayer::Draw()
{
    layerTexture_.draw(sceneText_);
    layerTexture_.draw(fpsText_);
    layerTexture_.draw(fpsNumberText_);
    layerTexture_.draw(nEntitiesText_);
    layerTexture_.draw(nEntitiesCountText_);
    layerTexture_.draw(dotShape_);
}

void HelperLayer::Update(float deltaTime)
{
    unsigned int fps = static_cast<unsigned int>(std::floor(1.0f / deltaTime));
    fpsNumberText_.setString(std::to_string(fps));
    nEntitiesCountText_.setString(std::to_string(nEntities_));
}

void HelperLayer::OnMessage(std::shared_ptr<Shared::Message> msg)
{
    if (msg->GetMessageType() == Shared::MessageType::EntityInitialized) {
        nEntities_++;
    }
    else if (msg->GetMessageType() == Shared::MessageType::EntityDestroyed) {
        nEntities_--;
    }
}

}  // namespace Scene

}  // namespace FA
