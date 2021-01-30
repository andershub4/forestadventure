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
#include "GameScene/GameSceneManager.h"
#include "GameScene/Transition/GameTransitionNone.h"

namespace FA {

class TextureManager;
class MessageBus;
class Message;

class GameScene
{
public:
    GameScene(GameSceneManager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
              GameSceneManager::SceneComponents& sceneComponents, GameSceneManager::SceneData& sceneData);
    virtual ~GameScene();

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

    void SwitchScene(std::unique_ptr<GameScene> newScene);

    template <class SceneT, class TransitionT = GameTransitionNone>
    void SwitchScene(const std::vector<SceneComponentId>& ids)
    {
        static_assert(std::is_base_of<GameScene, SceneT>::value, "SceneT must derive from GameScene");
        static_assert(std::is_base_of<GameTransition, TransitionT>::value,
                      "TransitionT must derive from GameTransition");

        sceneManager_.SetScene<SceneT, TransitionT>(messageBus_, textureManager_, ids);
    }

protected:
    GameSceneManager::SceneData& sceneData_;
    GameSceneManager::SceneComponents& sceneComponents_;
    TextureManager& textureManager_;
    MessageBus& messageBus_;

private:
    GameSceneManager& sceneManager_;
};

}  // namespace FA
