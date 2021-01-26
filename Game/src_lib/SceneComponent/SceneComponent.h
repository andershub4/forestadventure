/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

class MessageBus;
class Layer;

class SceneComponent
{
public:
    SceneComponent(MessageBus& messageBus);
    virtual ~SceneComponent();

    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(Layer& layer) = 0;

private:
    MessageBus& messageBus_;
};

}  // namespace FA
