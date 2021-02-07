/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Fwd/SfmlFwd.h"

namespace FA {

class MessageBus;
class TextureManager;
class BasicEffect;

namespace Scene {

class BasicScene;
class BasicComponent;

class BasicTransition
{
public:
    using CreateSceneFn = std::function<std::unique_ptr<BasicScene>(MessageBus&, TextureManager&)>;

    BasicTransition() = default;
    BasicTransition(float seconds, CreateSceneFn nextSceneFn);
    virtual ~BasicTransition();

    virtual void Update(float deltaTime) {}
    virtual std::unique_ptr<BasicEffect> CreateEffect(const sf::Vector2f& position, const sf::Vector2f& size) const = 0;

    std::unique_ptr<BasicScene> CreateNextScene(MessageBus& messageBus, TextureManager& textureManager) const;
    bool IsFinished() const;

protected:
    float seconds_ = 0;

private:
    sf::Clock clock_;
    CreateSceneFn nextSceneFn_;
    sf::Time targetTime_;
};

}  // namespace Scene

}  // namespace FA
