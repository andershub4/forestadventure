/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "LayerId.h"

namespace FA {

namespace Shared {

class MessageBus;
class Message;
enum class MessageType;

}  // namespace Shared

namespace Scene {

class BasicTransition;

class BasicLayer
{
public:
    BasicLayer(Shared::MessageBus& messageBus, const sf::IntRect& rect);
    virtual ~BasicLayer();

    virtual std::string Name() const = 0;
    virtual LayerId GetId() const = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void EnableInput(bool enable) = 0;
    virtual void EnterTransition(const BasicTransition& transition) {}
    virtual void ExitTransition(const BasicTransition& transition) {}
    virtual void OnLoad() {}
    virtual void OnCreate() {}
    virtual void SubscribeMessages() {}
    virtual void UnsubscribeMessages() {}

    void Clear();
    void DrawTo(sf::RenderTarget& renderTarget);

protected:
    sf::RenderTexture layerTexture_;

protected:
    void Subscribe(const std::vector<Shared::MessageType>& messageTypes);
    void Unsubscribe(const std::vector<Shared::MessageType>& messageTypes);

private:
    sf::Sprite sprite_;
    Shared::MessageBus& messageBus_;

private:
    virtual void OnMessage(std::shared_ptr<Shared::Message> msg) {}
};

}  // namespace Scene

}  // namespace FA
