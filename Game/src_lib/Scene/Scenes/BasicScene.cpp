/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicScene.h"

#include "Message/MessageBus.h"

namespace FA {

namespace Scene {

BasicScene::BasicScene(Manager &sceneManager, MessageBus &messageBus, TextureManager &textureManager,
                       Manager::Layers &layers, Manager::Data &data)
    : sceneManager_(sceneManager)
    , messageBus_(messageBus)
    , textureManager_(textureManager)
    , layers_(layers)
    , data_(data)
{}

BasicScene::~BasicScene() = default;

// TODO: Consider to request for sceneSwitch here, and do actual switch after Update().
// Then Update() can continue to execute code after the request is made.
void BasicScene::SwitchScene(std::unique_ptr<BasicScene> newScene)
{
    sceneManager_.SetScene(std::move(newScene));
}

void BasicScene::OnCloseWindow()
{
    data_.isRunning_ = false;
}

bool BasicScene::IsRunning() const
{
    return data_.isRunning_;
}

void BasicScene::Subscribe(const std::vector<MessageType> &messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes, [this](std::shared_ptr<Message> message) { OnMessage(message); });
}

void BasicScene::Unsubscribe(const std::vector<MessageType> &messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
}

}  // namespace Scene

}  // namespace FA
