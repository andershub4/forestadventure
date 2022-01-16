/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "AnimationShape.h"
#include "BasicShape.h"
#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/EntityService.h"
#include "ImageShape.h"
#include "RectangleShape.h"

namespace FA {

namespace Entity {

Shape::Shape(EntityService *entityService)
    : entityService_(entityService)
{}

Shape::~Shape() = default;

void Shape::Awake()
{
#ifdef _DEBUG
    auto r = std::make_shared<RectangleShape>();
    r->SetSize({1.0, 1.0});
    AddBasicShape(r);
#endif

    transform_ = entityService_->GetAttribute<TransformAttribute>();
    faceDirection_ = entityService_->GetAttribute<FaceDirectionAttribute>();

    for (auto &animation : animationShapes_) {
        animation->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
    for (auto &image : imageShapes_) {
        image->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
    for (auto &b : basicShapes_) {
        b->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
}

void Shape::Update(float deltaTime)
{
    for (auto &animation : animationShapes_) {
        animation->Update(deltaTime);
        animation->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
    for (auto &image : imageShapes_) {
        image->Update(deltaTime);
        image->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
    for (auto &b : basicShapes_) {
        b->SetTransform(transform_->GetPosition(), transform_->GetScale());
    }
}

void Shape::DrawTo(sf::RenderTarget &renderTarget)
{
    for (auto &animation : animationShapes_) {
        animation->DrawTo(renderTarget);
    }
    for (auto &image : imageShapes_) {
        image->DrawTo(renderTarget);
    }
    for (auto &b : basicShapes_) {
        b->DrawTo(renderTarget);
    }
}

void Shape::Set(FrameType frameType)
{
    for (auto &animation : animationShapes_) {
        animation->SetAnimation(frameType, faceDirection_->GetDirection());
    }
    for (auto &image : imageShapes_) {
        image->SetImage(frameType, faceDirection_->GetDirection());
    }
}

void Shape::AddAnimationShape(std::shared_ptr<AnimationShape> animation)
{
    animationShapes_.push_back(animation);
}

void Shape::AddImageShape(std::shared_ptr<ImageShape> image)
{
    imageShapes_.push_back(image);
}

void Shape::AddBasicShape(std::shared_ptr<BasicShape> basicShape)
{
    basicShapes_.push_back(basicShape);
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
