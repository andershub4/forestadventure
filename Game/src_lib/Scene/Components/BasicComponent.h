/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Enum/SceneComponentId.h"

namespace FA {

class MessageBus;
class Effect;

namespace Scene {

class BasicComponent
{
public:
    BasicComponent(MessageBus& messageBus);
    virtual ~BasicComponent();

    virtual SceneComponentId GetId() const = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void ProcessMessages(bool process) = 0;

    void Clear();
    void DrawTo(sf::RenderTarget& renderTarget);
    void Draw(const Effect& effect);

protected:
    sf::Sprite sprite_;
    sf::RenderTexture renderTexture_;

private:
    MessageBus& messageBus_;
};

}  // namespace Scene

}  // namespace FA
