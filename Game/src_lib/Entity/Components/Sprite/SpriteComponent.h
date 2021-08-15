/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity/Components/Animation/AnimationComponent.h"

namespace FA {

namespace Entity {

class TransformComponent;

class SpriteComponent
{
public:
    SpriteComponent(const TransformComponent &transform, const AnimationComponent &animation);
    virtual ~SpriteComponent();

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget);
    void Set(FrameType frameType, FaceDirection faceDir);
    bool AnimationIsCompleted() const;

private:
    sf::Sprite sprite_;
    const TransformComponent &transform_;
    AnimationComponent animation_;
};

}  // namespace Entity

}  // namespace FA
