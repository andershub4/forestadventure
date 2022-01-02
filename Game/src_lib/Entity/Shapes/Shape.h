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
class ImageShape;
class BasicShape;

class Shape
{
public:
    Shape(EntityService *entityService);
    virtual ~Shape();

    void Awake();
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    void Set(FrameType frameType);
    void AddAnimationShape(std::shared_ptr<AnimationShape> animation);
    void AddImageShape(std::shared_ptr<ImageShape> image);
    void AddBasicShape(std::shared_ptr<BasicShape> basicShape);
    bool AnimationIsCompleted() const;

private:
    EntityService *entityService_ = nullptr;
    std::shared_ptr<TransformAttribute> transform_ = nullptr;
    std::shared_ptr<FaceDirectionAttribute> faceDirection_ = nullptr;
    std::vector<std::shared_ptr<AnimationShape>> animationShapes_;
    std::vector<std::shared_ptr<ImageShape>> imageShapes_;
    std::vector<std::shared_ptr<BasicShape>> basicShapes_;
};

}  // namespace Entity

}  // namespace FA
