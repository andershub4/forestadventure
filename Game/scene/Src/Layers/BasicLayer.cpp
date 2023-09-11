/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicLayer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Message/MessageBus.h"

namespace FA {

namespace Scene {

BasicLayer::BasicLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect)
    : messageBus_(messageBus)
{
    layerTexture_.create(rect.width, rect.height);
    sprite_.setTexture(layerTexture_.getTexture());
    sprite_.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
}

BasicLayer::~BasicLayer() = default;

void BasicLayer::Clear()
{
    layerTexture_.clear(sf::Color::Transparent);
}

void BasicLayer::DrawTo(Graphic::IRenderTarget& renderTarget)
{
    layerTexture_.display();
    renderTarget.draw(sprite_);
}

void BasicLayer::Subscribe(const std::vector<Shared::MessageType>& messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes,
                              [this](std::shared_ptr<Shared::Message> message) { OnMessage(message); });
}

void BasicLayer::Unsubscribe(const std::vector<Shared::MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
}

}  // namespace Scene

}  // namespace FA
