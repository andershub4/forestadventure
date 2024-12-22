/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#ifdef _DEBUG
#include "RectangleShape.h"
#endif

#include "ShapeParts/AnimationPartIf.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Entity {

struct Body;

class Shape
{
public:
    Shape(Body &body);
    ~Shape();

    void RegisterMainShapePart(std::shared_ptr<AnimationPartIf> part);
    void RegisterMainColliderPart(std::shared_ptr<AnimationPartIf> part);
    void RegisterShapePart(std::shared_ptr<AnimationPartIf> part);
    void RegisterColliderPart(std::shared_ptr<AnimationPartIf> part);
    void Enter();
    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf &renderTarget) const;
    bool Intersect(const Shape &shape) const;

private:
    std::shared_ptr<AnimationPartIf> mainShapePart;
    std::shared_ptr<AnimationPartIf> mainColliderPart;
    std::vector<std::shared_ptr<AnimationPartIf>> colliderParts_;
    std::vector<std::shared_ptr<AnimationPartIf>> shapeParts_;
    Body &body_;
#ifdef _DEBUG
    Graphic::RectangleShape rShape_;
#endif  // _DEBUG
};

}  // namespace Entity

}  // namespace FA
