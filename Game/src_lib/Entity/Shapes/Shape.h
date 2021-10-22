/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "Fwd/SfmlFwd.h"

#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class TransformAttribute;
class FaceDirectionAttribute;
class EntityService;
class AnimationShape;

class Shape
{
public:
    Shape(EntityService *owner);
    virtual ~Shape();

    void Awake();
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    void Set(FrameType frameType);
    void AddAnimationShape(std::shared_ptr<AnimationShape> animation);
    bool AnimationIsCompleted() const;

private:
    EntityService *entityService_ = nullptr;
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
    std::vector<std::shared_ptr<AnimationShape>> animationShapes_;
};

}  // namespace Entity

}  // namespace FA
