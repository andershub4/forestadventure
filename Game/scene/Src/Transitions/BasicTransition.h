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

#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Shared {

class MessageBus;
class BasicEffect;

}  // namespace Shared

namespace Scene {

class BasicScene;
class BasicLayer;

class BasicTransition
{
public:
    using CreateSceneFn = std::function<std::unique_ptr<BasicScene>(Shared::MessageBus&, Shared::TextureManager&)>;

    BasicTransition() = default;
    BasicTransition(float seconds, CreateSceneFn nextSceneFn);
    virtual ~BasicTransition();

    virtual void Update(float deltaTime) {}
    virtual std::unique_ptr<Shared::BasicEffect> CreateEffect(const sf::Vector2f& position,
                                                              const sf::Vector2f& size) const = 0;

    std::unique_ptr<BasicScene> CreateNextScene(Shared::MessageBus& messageBus,
                                                Shared::TextureManager& textureManager) const;
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
