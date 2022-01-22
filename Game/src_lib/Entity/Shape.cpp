/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Attributes/FaceDirectionAttribute.h"
#include "Entity/Attributes/TransformAttribute.h"
#include "Entity/EntityService.h"

namespace FA {

namespace Entity {

Shape::Shape(EntityService *entityService)
    : entityService_(entityService)
{}

Shape::~Shape() = default;

void Shape::Register()
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
    transform_ = entityService_->GetAttribute<TransformAttribute>();
    faceDirection_ = entityService_->GetAttribute<FaceDirectionAttribute>();
}

void Shape::Update(float deltaTime)
{
    if (currentAnimation_.IsValid()) {
        currentAnimation_.Update(deltaTime);
        currentAnimation_.ApplyTo(animationSprite_);
        animationSprite_.setPosition(transform_->GetPosition());
        animationSprite_.setScale(transform_->GetScale(), transform_->GetScale());
    }

    if (currentImage_.IsValid()) {
        imageSprite_.setPosition(transform_->GetPosition());
        imageSprite_.setScale(transform_->GetScale(), transform_->GetScale());
    }

#ifdef _DEBUG
    rShape_.setPosition(transform_->GetPosition());
    rShape_.setScale(transform_->GetScale(), transform_->GetScale());
#endif
}

void Shape::DrawTo(sf::RenderTarget &renderTarget)
{
    if (currentAnimation_.IsValid()) {
        renderTarget.draw(animationSprite_);
    }
    if (currentImage_.IsValid()) {
        renderTarget.draw(imageSprite_);
    }
#ifdef _DEBUG
    renderTarget.draw(rShape_);
#endif
}

void Shape::SetAnimation(const Animation &animation)
{
    if (animation.IsValid()) {
        currentAnimation_ = animation;
        currentAnimation_.ApplyTo(animationSprite_);
        animationSprite_.setOrigin(animationSprite_.getLocalBounds().width / 2,
                                   animationSprite_.getLocalBounds().height / 2);
        currentAnimation_.Start();
    }
}

void Shape::SetImage(const Image &image)
{
    if (image.IsValid()) {
        currentImage_ = image;
        currentImage_.ApplyTo(imageSprite_);
        imageSprite_.setOrigin(imageSprite_.getLocalBounds().width / 2, imageSprite_.getLocalBounds().height / 2);
    }
}

bool Shape::AnimationIsCompleted() const
{
    return currentAnimation_.IsValid() ? currentAnimation_.IsCompleted() : true;
}

}  // namespace Entity

}  // namespace FA
