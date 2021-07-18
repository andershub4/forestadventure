/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Scene/ComponentId.h"

namespace FA {

class MessageBus;
class BasicEffect;

namespace Scene {

class BasicTransition;
struct Layer;

class BasicComponent
{
public:
    BasicComponent(MessageBus& messageBus, const Layer& layer);
    virtual ~BasicComponent();

    virtual ComponentId GetId() const = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void EnableInput(bool enable) = 0;
    virtual void EnterTransition(const BasicTransition& transition) {}
    virtual void ExitTransition(const BasicTransition& transition) {}

    void Clear();
    void DrawTo(sf::RenderTarget& renderTarget);

protected:
    sf::RenderTexture layerTexture_;

private:
    sf::Sprite sprite_;
    MessageBus& messageBus_;
};

}  // namespace Scene

}  // namespace FA
