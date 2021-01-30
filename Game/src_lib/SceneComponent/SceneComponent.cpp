/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "SceneComponent.h"

#include "Constant/Screen.h"
#include "Effect/Effect.h"

namespace FA {

SceneComponent::SceneComponent(MessageBus& messageBus)
    : messageBus_(messageBus)
{
    renderTexture_.create(constant::Screen::width, constant::Screen::height);
    sprite_.setTexture(renderTexture_.getTexture());
}

SceneComponent::~SceneComponent() = default;

void SceneComponent::Clear()
{
    renderTexture_.clear(sf::Color::Transparent);
}

void SceneComponent::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTexture_.display();
    renderTarget.draw(sprite_);
}

void SceneComponent::Draw(const Effect& effect)
{
    effect.DrawTo(renderTexture_);
}

}  // namespace FA
