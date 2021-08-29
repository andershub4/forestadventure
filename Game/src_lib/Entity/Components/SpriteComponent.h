/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "AnimationComponent.h"
#include "BasicComponent.h"

namespace FA {

namespace Entity {

class TransformComponent;

class SpriteComponent : public BasicComponent
{
public:
    SpriteComponent(const TransformComponent &transform, const AnimationComponent &animation);
    virtual ~SpriteComponent();

    virtual void Update(float deltaTime) override;

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
