/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "BasicComponent.h"

namespace FA {

namespace Scene {

class IntroComponent : public BasicComponent
{
public:
    IntroComponent(MessageBus& messageBus);
    virtual ~IntroComponent();

    virtual ComponentId GetId() const override { return ComponentId::Intro; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void EnableInput(bool enable) override {}

private:
    sf::RectangleShape rect_;
};

}  // namespace Scene

}  // namespace FA
