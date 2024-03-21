/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <map>
#include <memory>

#include "Resource/TextureManager.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

class MessageBus;
class Message;

}  // namespace Shared

namespace Scene {

class BasicScene;
class BasicTransition;
class BasicLayer;
enum class LayerId;

class Manager
{
public:
    using Layers = std::map<LayerId, std::unique_ptr<BasicLayer>>;

    struct Data
    {
        bool isRunning_ = true;
    };

    Manager(Shared::MessageBus& messageBus, Shared::TextureManager& textureManager);
    ~Manager();

    template <class SceneT, class TransitionT>
    void SetScene(Shared::MessageBus& messageBus, Shared::TextureManager& textureManager)
    {
        auto createSceneFn = [this](Shared::MessageBus& messageBus, Shared::TextureManager& textureManager) {
            return std::make_unique<SceneT>(*this, messageBus, textureManager, layers_, data_);
        };

        auto transition = std::make_unique<TransitionT>(createSceneFn);
        SetTransitionScene(messageBus, textureManager, std::move(transition));
    }

    void SetScene(std::unique_ptr<BasicScene> newScene);

    void DrawTo(Graphic::RenderTargetIf& renderTarget);
    void Update(float deltaTime);

    bool IsRunning() const;

private:
    std::unique_ptr<BasicScene> currentScene_;
    Data data_;
    Layers layers_;

    void SetTransitionScene(Shared::MessageBus& messageBus, Shared::TextureManager& textureManager,
                            std::unique_ptr<BasicTransition> transition);
};

}  // namespace Scene

}  // namespace FA
