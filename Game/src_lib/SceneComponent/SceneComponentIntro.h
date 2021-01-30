/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "SceneComponent.h"

namespace FA {

class SceneComponentIntro : public SceneComponent
{
public:
    SceneComponentIntro(MessageBus& messageBus);
    virtual ~SceneComponentIntro();

    virtual SceneComponentId GetId() const override { return SceneComponentId::Intro; }
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

private:
    sf::RectangleShape rect_;
};

}  // namespace FA
