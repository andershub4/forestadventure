/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicComponent.h"

#include "Constant/Screen.h"
#include "Effect/Effect.h"

namespace FA {

namespace Scene {

BasicComponent::BasicComponent(MessageBus& messageBus)
    : messageBus_(messageBus)
{
    renderTexture_.create(constant::Screen::width, constant::Screen::height);
    sprite_.setTexture(renderTexture_.getTexture());
}

BasicComponent::~BasicComponent() = default;

void BasicComponent::Clear()
{
    renderTexture_.clear(sf::Color::Transparent);
}

void BasicComponent::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTexture_.display();
    renderTarget.draw(sprite_);
}

void BasicComponent::Draw(const Effect& effect)
{
    effect.DrawTo(renderTexture_);
}

}  // namespace Scene

}  // namespace FA
