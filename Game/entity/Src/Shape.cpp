/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include "Body.h"
#include "RenderTargetIf.h"
#include "Sprite.h"

namespace FA {

namespace Entity {

Shape::Shape(Body &body)
    : body_(body)
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

Shape::~Shape() = default;

void Shape::Enter()
{
    for (auto part : shapeParts_) {
        part->Enter();
        part->SetPosition(body_.position_);
        part->SetRotation(body_.rotation_);
    }

    for (auto part : colliderParts_) {
        part->Enter();
        part->SetPosition(body_.position_);
        part->SetRotation(body_.rotation_);
    }

#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif
}

void Shape::Update(float deltaTime)
{
    for (auto part : shapeParts_) {
        part->Update(deltaTime);
        part->SetPosition(body_.position_);
        part->SetRotation(body_.rotation_);
    }

    for (auto part : colliderParts_) {
        part->Update(deltaTime);
        part->SetPosition(body_.position_);
        part->SetRotation(body_.rotation_);
    }

#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif  // _DEBUG
}

void Shape::RegisterShapePart(std::shared_ptr<BasicAnimationPart> part)
{
    shapeParts_.push_back(part);
}

void Shape::RegisterColliderPart(std::shared_ptr<BasicAnimationPart> part)
{
    colliderParts_.push_back(part);
}

void Shape::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto part : shapeParts_) {
        part->DrawTo(renderTarget);
    }

#ifdef _DEBUG
    for (auto part : colliderParts_) {
        part->DrawTo(renderTarget);
    }
#endif  // _DEBUG

#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

bool Shape::Intersect(const Shape &otherShape) const
{
    bool intersect = false;

    for (auto part : colliderParts_) {
        for (auto otherPart : otherShape.colliderParts_) {
            intersect |= part->Intersects(*otherPart);
        }
    }

    return intersect;
}

}  // namespace Entity

}  // namespace FA
