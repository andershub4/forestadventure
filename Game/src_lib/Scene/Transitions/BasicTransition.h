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

class MessageBus;
class TextureManager;

namespace Scene {

class BasicScene;
class BasicComponent;

class BasicTransition
{
public:
    using CreateSceneFn = std::function<std::unique_ptr<BasicScene>(MessageBus&, TextureManager&)>;

    BasicTransition() = default;
    BasicTransition(CreateSceneFn nextSceneFn);
    virtual ~BasicTransition();

    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual void DrawTo(BasicComponent& component) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual bool IsFinished() const = 0;

    std::unique_ptr<BasicScene> CreateNextScene(MessageBus& messageBus, TextureManager& textureManager) const;

private:
    CreateSceneFn nextSceneFn_;
};

}  // namespace Scene

}  // namespace FA
