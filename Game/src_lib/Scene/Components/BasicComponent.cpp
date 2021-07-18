/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicComponent.h"

#include "Scene/Layer.h"

namespace FA {

namespace Scene {

BasicComponent::BasicComponent(MessageBus& messageBus, const Layer& layer)
    : messageBus_(messageBus)
{
    layerTexture_.create(layer.width_, layer.height_);
    sprite_.setTexture(layerTexture_.getTexture());
    sprite_.setPosition(layer.x_, layer.y_);
}

BasicComponent::~BasicComponent() = default;

void BasicComponent::Clear()
{
    layerTexture_.clear(sf::Color::Transparent);
}

void BasicComponent::DrawTo(sf::RenderTarget& renderTarget)
{
    layerTexture_.display();
    renderTarget.draw(sprite_);
}

}  // namespace Scene

}  // namespace FA
