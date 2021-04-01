/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicComponent.h"

#include "Constant/Screen.h"

namespace FA {

namespace Scene {

BasicComponent::BasicComponent(MessageBus& messageBus)
    : messageBus_(messageBus)
{
    layer_.create(constant::Screen::width, constant::Screen::height);
    sprite_.setTexture(layer_.getTexture());
}

BasicComponent::~BasicComponent() = default;

void BasicComponent::Clear()
{
    layer_.clear(sf::Color::Transparent);
}

void BasicComponent::DrawTo(sf::RenderTarget& renderTarget)
{
    layer_.display();
    renderTarget.draw(sprite_);
}

}  // namespace Scene

}  // namespace FA
