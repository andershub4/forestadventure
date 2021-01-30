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

class SceneComponent
{
public:
    SceneComponent(MessageBus& messageBus);
    virtual ~SceneComponent();

    virtual SceneComponentId GetId() const = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    void Clear();
    void DrawTo(sf::RenderTarget& renderTarget);
    void Draw(const Effect& effect);

protected:
    sf::Sprite sprite_;
    sf::RenderTexture renderTexture_;

private:
    MessageBus& messageBus_;
};

}  // namespace FA
