/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>

#include "Resource/TextureManager.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class IRectangleShape;

}  // namespace Graphic

namespace Shared {

class MessageBus;
class EffectIf;

}  // namespace Shared

namespace Scene {

class BasicScene;
class BasicLayer;

class BasicTransition
{
public:
    using CreateSceneFn = std::function<std::unique_ptr<BasicScene>(Shared::MessageBus&, Shared::TextureManager&)>;

    BasicTransition() = default;
    BasicTransition(float duration, CreateSceneFn nextSceneFn);
    virtual ~BasicTransition();

    virtual void Update(float deltaTime) {}
    virtual std::unique_ptr<Shared::EffectIf> CreateEffect(std::shared_ptr<Graphic::IRectangleShape> rect,
                                                           const sf::Vector2f& position) const = 0;

    std::unique_ptr<BasicScene> CreateNextScene(Shared::MessageBus& messageBus,
                                                Shared::TextureManager& textureManager) const;
    virtual bool IsFinished() const { return true; }

protected:
    float duration_ = 0;

private:
    CreateSceneFn nextSceneFn_;
};

}  // namespace Scene

}  // namespace FA
