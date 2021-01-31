/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "Fwd/SfmlFwd.h"
#include "Scene/Manager.h"
#include "Scene/Transitions/NullTransition.h"

namespace FA {

class TextureManager;
class MessageBus;
class Message;

namespace Scene {

class BasicScene
{
public:
    BasicScene(Manager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
               Manager::Components& components, Manager::Data& data);
    virtual ~BasicScene();

    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual std::string Name() const = 0;

    virtual void OnKeyPressed(std::shared_ptr<Message> message) {}
    virtual void OnKeyReleased(std::shared_ptr<Message> message) {}
    virtual void OnIsKeyPressed(std::shared_ptr<Message> message) {}
    virtual void OnCloseWindow(std::shared_ptr<Message> message);
    virtual void Enter() {}
    virtual void Exit() {}

    bool IsRunning() const;

    void SwitchScene(std::unique_ptr<BasicScene> newScene);

    template <class SceneT, class TransitionT = NullTransition>
    void SwitchScene(const std::vector<ComponentId>& ids)
    {
        static_assert(std::is_base_of<BasicScene, SceneT>::value, "SceneT must derive from BasicScene");
        static_assert(std::is_base_of<BasicTransition, TransitionT>::value,
                      "TransitionT must derive from BasicTransition");

        sceneManager_.SetScene<SceneT, TransitionT>(messageBus_, textureManager_, ids);
    }

protected:
    Manager::Data& data_;
    Manager::Components& components_;
    TextureManager& textureManager_;
    MessageBus& messageBus_;

private:
    Manager& sceneManager_;
};

}  // namespace Scene

}  // namespace FA
