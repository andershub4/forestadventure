/*
 *	Copyright (C) 2021 Anders Wennmo
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

Shape::Shape(EntityService *owner)
    : entityService_(owner)
{}

Shape::~Shape() = default;

void Shape::Awake()
{
    transform_ = entityService_->GetAttribute<TransformAttribute>();
    faceDirection_ = entityService_->GetAttribute<FaceDirectionAttribute>();

    sprite_.setPosition(transform_->GetPosition());
    sprite_.setScale(transform_->GetScale(), transform_->GetScale());

    animation_->Init();
}

void Shape::Update(float deltaTime)
{
    animation_->Update(deltaTime);
    animation_->ApplyTo(sprite_);

    sprite_.setPosition(transform_->GetPosition());
    sprite_.setScale(transform_->GetScale(), transform_->GetScale());
}

void Shape::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void Shape::Set(FrameType frameType)
{
    animation_->SetAnimation(frameType, faceDirection_->GetDirection());
    animation_->ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void Shape::Init()
{
    //    animation_->Init();
}

bool Shape::AnimationIsCompleted() const
{
    return animation_->IsCompleted();
}

}  // namespace Entity

}  // namespace FA
