/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IntroComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Scene {

IntroComponent::IntroComponent(MessageBus& messageBus)
    : BasicComponent(messageBus)
{
    rect_.setSize(sf::Vector2f(constant::Screen::width_f, 24.0));
    rect_.setPosition(0.0, constant::Screen::centerY_f);
}

IntroComponent::~IntroComponent() = default;

void IntroComponent::Draw()
{
    renderTexture_.draw(rect_);
}

void IntroComponent::Update(float deltaTime)
{}

}  // namespace Scene

}  // namespace FA
