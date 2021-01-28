/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>
#include <string>

#include "Enum/SceneComponentId.h"
#include "Fwd/SfmlFwd.h"
#include "SceneComponent/SceneComponent.h"

namespace FA {

class GameSceneManager;
class TextureManager;
class MessageBus;
class Message;

class GameScene
{
public:
    using SceneComponents = std::map<SceneComponentId, std::unique_ptr<SceneComponent>>;

    struct SceneData
    {
        bool isRunning_ = true;
    };

    GameScene(GameSceneManager& sceneManager, MessageBus& messageBus, TextureManager& textureManager,
              SceneComponents& sceneComponents, SceneData& sceneData);
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

    template <class SceneT>
    void SwitchScene()
    {
        static_assert(std::is_base_of<GameScene, SceneT>::value, "SceneT must derive from GameScene");

        SwitchScene(
            std::make_unique<SceneT>(sceneManager_, messageBus_, textureManager_, sceneComponents_, sceneData_));
    }

protected:
    SceneData& sceneData_;
    SceneComponents& sceneComponents_;
    TextureManager& textureManager_;
    MessageBus& messageBus_;

private:
    GameSceneManager& sceneManager_;
};

}  // namespace FA
