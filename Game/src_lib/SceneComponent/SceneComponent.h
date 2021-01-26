/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Game/Layer.h"

namespace FA {

class MessageBus;

class SceneComponent
{
public:
    SceneComponent(MessageBus& messageBus);
    virtual ~SceneComponent();

    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;

protected:
    Layer layer_;

private:
    MessageBus& messageBus_;
};

}  // namespace FA
