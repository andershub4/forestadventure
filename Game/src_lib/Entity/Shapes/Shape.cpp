/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "AnimationShape.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/EntityService.h"

namespace FA {

namespace Entity {

Shape::Shape(EntityService *owner)
    : entityService_(owner)
{}

Shape::~Shape() = default;

void Shape::Awake()
{
    transform_ = entityService_->GetAttribute<TransformAttribute>();
    faceDirection_ = entityService_->GetAttribute<FaceDirectionAttribute>();

    for (auto &animation : animationShapes_) {
        animation->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
}

void Shape::Update(float deltaTime)
{
    for (auto &animation : animationShapes_) {
        animation->Update(deltaTime);
        animation->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
}

void Shape::DrawTo(sf::RenderTarget &renderTarget)
{
    for (auto &animation : animationShapes_) {
        animation->DrawTo(renderTarget);
    }
}

void Shape::Set(FrameType frameType)
{
    for (auto &animation : animationShapes_) {
        animation->SetAnimation(frameType, faceDirection_->GetDirection());
    }
}

void Shape::AddAnimationShape(std::shared_ptr<AnimationShape> animation)
{
    animationShapes_.push_back(animation);
}

bool Shape::AnimationIsCompleted() const
{
    bool result = true;
    for (const auto &animation : animationShapes_) {
        result &= animation->IsCompleted();
    }

    return result;
}

}  // namespace Entity

}  // namespace FA
