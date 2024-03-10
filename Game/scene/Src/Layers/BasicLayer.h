/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "LayerId.h"
#include "RenderTexture.h"
#include "SfmlFwd.h"
#include "Sprite.h"

namespace FA {

namespace Graphic {

class IRenderTarget;

}  // namespace Graphic

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
    virtual void EnterTransition(BasicTransition& transition) {}
    virtual void ExitTransition(BasicTransition& transition) {}
    virtual void DrawTransition(const BasicTransition& transition) {}
    virtual void OnLoad() {}
    virtual void OnCreate() {}
    virtual void SubscribeMessages() {}
    virtual void UnsubscribeMessages() {}

    void Clear();
    void DrawTo(Graphic::IRenderTarget& renderTarget);

protected:
    Graphic::RenderTexture layerTexture_;

protected:
    void Subscribe(const std::vector<Shared::MessageType>& messageTypes);
    void Unsubscribe(const std::vector<Shared::MessageType>& messageTypes);

private:
    Graphic::Sprite sprite_;
    Shared::MessageBus& messageBus_;

private:
    virtual void OnMessage(std::shared_ptr<Shared::Message> msg) {}
};

}  // namespace Scene

}  // namespace FA
