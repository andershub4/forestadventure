/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>

#include "Enum/SceneComponentId.h"
#include "Fwd/SfmlFwd.h"
#include "SceneComponent/SceneComponent.h"

namespace FA {

class GameScene;
class MessageBus;
class TextureManager;
class Message;
class GameTransition;

class GameSceneManager
{
public:
    using SceneComponents = std::map<SceneComponentId, std::unique_ptr<SceneComponent>>;

    struct SceneData
    {
        bool isRunning_ = true;
    };

    GameSceneManager(MessageBus& messageBus, TextureManager& textureManager);
    ~GameSceneManager();

    template <class SceneT, class TransitionT>
    void SetScene(MessageBus& messageBus, TextureManager& textureManager, const std::vector<SceneComponentId>& ids)
    {
        auto createStateCB = [this](MessageBus& messageBus, TextureManager& textureManager) {
            return std::make_unique<SceneT>(*this, messageBus, textureManager, sceneComponents_, sceneData_);
        };

        auto transition = std::make_unique<TransitionT>(createStateCB);
        SetTransitionScene(messageBus, textureManager, std::move(transition), ids);
    }

    void SetScene(std::unique_ptr<GameScene> newScene);

    void DrawTo(sf::RenderTarget& renderTarget);
    void Update(float deltaTime);

    bool IsRunning() const;

    void OnKeyPressed(std::shared_ptr<Message> message);
    void OnKeyReleased(std::shared_ptr<Message> message);
    void OnIsKeyPressed(std::shared_ptr<Message> message);
    void OnCloseWindow(std::shared_ptr<Message> message);

private:
    std::unique_ptr<GameScene> currentScene_;
    SceneData sceneData_;
    SceneComponents sceneComponents_;

    void SetTransitionScene(MessageBus& messageBus, TextureManager& textureManager,
                            std::unique_ptr<GameTransition> transition, const std::vector<SceneComponentId>& ids);
};

}  // namespace FA
