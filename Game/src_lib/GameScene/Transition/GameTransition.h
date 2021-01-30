/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>

#include "Fwd/SfmlFwd.h"

namespace FA {

class GameScene;
class MessageBus;
class TextureManager;
class SceneComponent;

class GameTransition
{
public:
    using CreateSceneFn = std::function<std::unique_ptr<GameScene>(MessageBus&, TextureManager&)>;

    GameTransition() = default;
    GameTransition(CreateSceneFn nextSceneFn);
    virtual ~GameTransition();

    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual void DrawTo(SceneComponent& sceneComponent) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual bool IsFinished() const = 0;

    std::unique_ptr<GameScene> CreateNextScene(MessageBus& messageBus, TextureManager& textureManager) const;

private:
    CreateSceneFn nextSceneFn_;
};

}  // namespace FA
