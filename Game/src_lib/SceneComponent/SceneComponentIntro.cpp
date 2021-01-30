/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SceneComponentIntro.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Message/MessageBus.h"

namespace FA {

SceneComponentIntro::SceneComponentIntro(MessageBus& messageBus)
    : SceneComponent(messageBus)
{
    rect_.setSize(sf::Vector2f(constant::Screen::width_f, 24.0));
    rect_.setPosition(0.0, constant::Screen::centerY_f);
}

SceneComponentIntro::~SceneComponentIntro() = default;

void SceneComponentIntro::Draw()
{
    renderTexture_.draw(rect_);
}

void SceneComponentIntro::Update(float deltaTime)
{}

}  // namespace FA
