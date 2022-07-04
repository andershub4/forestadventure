/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Scene/LayerId.h"

namespace FA {

class MessageBus;
class Message;
class BasicEffect;
enum class MessageType;

namespace Scene {

class BasicTransition;

class BasicLayer
{
public:
    BasicLayer(MessageBus& messageBus, const sf::IntRect& rect);
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
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);

private:
    sf::Sprite sprite_;
    MessageBus& messageBus_;

private:
    virtual void OnMessage(std::shared_ptr<Message> msg) {}
};

}  // namespace Scene

}  // namespace FA
