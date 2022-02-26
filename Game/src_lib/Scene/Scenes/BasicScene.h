/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Fwd/SfmlFwd.h"
#include "Resource/TextureManager.h"
#include "Scene/Manager.h"
#include "Scene/Transitions/NullTransition.h"

namespace FA {

class MessageBus;
enum class MessageType;

namespace Scene {

class BasicScene
{
public:
    BasicScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager, Manager::Layers& layers,
               Manager::Data& data);
    virtual ~BasicScene();

    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual std::string Name() const = 0;

    virtual void Enter() {}
    virtual void Exit() {}

    bool IsRunning() const;

    void SwitchScene(std::unique_ptr<BasicScene> newScene);

    template <class SceneT, class TransitionT = NullTransition>
    void SwitchScene()
    {
        static_assert(std::is_base_of<BasicScene, SceneT>::value, "SceneT must derive from BasicScene");
        static_assert(std::is_base_of<BasicTransition, TransitionT>::value,
                      "TransitionT must derive from BasicTransition");

        sceneManager_.SetScene<SceneT, TransitionT>(messageBus_, textureManager_);
    }

protected:
    Manager::Data& data_;
    Manager::Layers& layers_;
    TextureManager& textureManager_;
    MessageBus& messageBus_;

protected:
    void Subscribe(const std::vector<MessageType>& messageTypes);
    void Unsubscribe(const std::vector<MessageType>& messageTypes);
    void OnCloseWindow();

private:
    Manager& sceneManager_;

private:
    virtual void OnMessage(std::shared_ptr<Message> msg) {}
};

}  // namespace Scene

}  // namespace FA
