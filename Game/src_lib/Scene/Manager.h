/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>

#include "ComponentId.h"
#include "Components/BasicComponent.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class TextureManager;
class Message;

namespace Scene {

class BasicScene;
class BasicTransition;

class Manager
{
public:
    using Components = std::map<ComponentId, std::unique_ptr<BasicComponent>>;

    struct Data
    {
        bool isRunning_ = true;
    };

    Manager(MessageBus& messageBus, TextureManager& textureManager);
    ~Manager();

    template <class SceneT, class TransitionT>
    void SetScene(MessageBus& messageBus, TextureManager& textureManager, const std::vector<ComponentId>& ids)
    {
        auto createStateCB = [this](MessageBus& messageBus, TextureManager& textureManager) {
            return std::make_unique<SceneT>(*this, messageBus, textureManager, components_, data_);
        };

        auto transition = std::make_unique<TransitionT>(createStateCB);
        SetTransitionScene(messageBus, textureManager, std::move(transition), ids);
    }

    void SetScene(std::unique_ptr<BasicScene> newScene);

    void DrawTo(sf::RenderTarget& renderTarget);
    void Update(float deltaTime);

    bool IsRunning() const;

    void OnKeyPressed(std::shared_ptr<Message> message);
    void OnKeyReleased(std::shared_ptr<Message> message);
    void OnIsKeyPressed(std::shared_ptr<Message> message);
    void OnCloseWindow(std::shared_ptr<Message> message);

private:
    std::unique_ptr<BasicScene> currentScene_;
    Data data_;
    Components components_;

    void SetTransitionScene(MessageBus& messageBus, TextureManager& textureManager,
                            std::unique_ptr<BasicTransition> transition, const std::vector<ComponentId>& ids);
};

}  // namespace Scene

}  // namespace FA
