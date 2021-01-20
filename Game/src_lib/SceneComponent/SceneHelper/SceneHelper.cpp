/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SceneHelper.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Game/Layer.h"
#include "Message/MessageBus.h"
#include "Utils/Logger.h"

namespace FA {

SceneHelper::SceneHelper(MessageBus& messageBus, const std::string& sceneName)
    : messageBus_(messageBus)
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

    dotShape_.setSize(sf::Vector2f(1.0, 1.0));
    dotShape_.setPosition(constant::Screen::centerX_f, constant::Screen::centerY_f);
}

SceneHelper::~SceneHelper() = default;

void SceneHelper::DrawTo(Layer& layer)
{
    layer.Clear();
    layer.Draw(sceneText_);
    layer.Draw(dotShape_);
    layer.Display();
}

void SceneHelper::Update(float deltaTime)
{}

}  // namespace FA
