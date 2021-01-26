/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SceneComponentHelper.h"

#include <cmath>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Game/Layer.h"
#include "Message/MessageBus.h"
#include "Utils/Logger.h"

namespace FA {

SceneComponentHelper::SceneComponentHelper(MessageBus& messageBus, const std::string& sceneName)
    : SceneComponent(messageBus)
{
    if (!font_.loadFromFile("assets/font/cello-sans/hinted-CelloSans-Medium.ttf")) {
        LOG_ERROR("Could not load hinted-CelloSans-Medium");
    }

    sceneText_.setFont(font_);
    sceneText_.setString(sceneName);
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

    dotShape_.setSize(sf::Vector2f(1.0, 1.0));
    dotShape_.setPosition(constant::Screen::centerX_f, constant::Screen::centerY_f);
}

SceneComponentHelper::~SceneComponentHelper() = default;

void SceneComponentHelper::DrawTo(Layer& layer)
{
    layer.Clear();
    layer.Draw(sceneText_);
    layer.Draw(fpsText_);
    layer.Draw(fpsNumberText_);
    layer.Draw(dotShape_);
    layer.Display();
}

void SceneComponentHelper::Update(float deltaTime)
{
    unsigned int fps = static_cast<unsigned int>(std::floor(1.0f / deltaTime));
    fpsNumberText_.setString(std::to_string(fps));
}

}  // namespace FA
