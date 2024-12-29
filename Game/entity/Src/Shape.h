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

namespace FA {

namespace Graphic {

class RenderTargetIf;
class SpriteIf;
class RectangleShapeIf;

}  // namespace Graphic

namespace Shared {

struct ImageFrame;
struct ColliderFrame;

}  // namespace Shared

namespace Entity {

struct Body;
template <class T>
class AnimatorIf;

class Shape
{
public:
    Shape(Body &body);
    ~Shape();

    std::shared_ptr<Graphic::SpriteIf> RegisterSprite();
    std::shared_ptr<Graphic::RectangleShapeIf> RegisterCollider();
    void RegisterImageAnimator(std::shared_ptr<AnimatorIf<Shared::ImageFrame>> animator);
    void RegisterColliderAnimator(std::shared_ptr<AnimatorIf<Shared::ColliderFrame>> animator);
    void Enter();
    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf &renderTarget) const;
    bool Intersect(const Shape &shape) const;

private:
    std::vector<std::shared_ptr<AnimatorIf<Shared::ImageFrame>>> imageAnimators_;
    std::vector<std::shared_ptr<AnimatorIf<Shared::ColliderFrame>>> colliderAnimators_;
    std::vector<std::shared_ptr<Graphic::SpriteIf>> sprites_;
    std::vector<std::shared_ptr<Graphic::RectangleShapeIf>> colliders_;
    Body &body_;
#ifdef _DEBUG
    Graphic::RectangleShape rShape_;
#endif  // _DEBUG
};

}  // namespace Entity

}  // namespace FA
