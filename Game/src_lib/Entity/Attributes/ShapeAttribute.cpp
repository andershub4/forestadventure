/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ShapeAttribute.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/PropertyHandler.h"
#include "FaceDirectionAttribute.h"
#include "TransformAttribute.h"

namespace FA {

namespace Entity {

ShapeAttribute::ShapeAttribute(PropertyHandler *owner)
    : BasicAttribute(owner)
{}

ShapeAttribute::~ShapeAttribute() = default;

void ShapeAttribute::Awake()
{
    transform_ = Owner()->GetAttribute<TransformAttribute>();
    faceDirection_ = Owner()->GetAttribute<FaceDirectionAttribute>();

    sprite_.setPosition(transform_->GetPosition());
    sprite_.setScale(transform_->GetScale(), transform_->GetScale());
}

void ShapeAttribute::Update(float deltaTime)
{
    animation_->Update(deltaTime);
    animation_->ApplyTo(sprite_);

    sprite_.setPosition(transform_->GetPosition());
    sprite_.setScale(transform_->GetScale(), transform_->GetScale());
}

void ShapeAttribute::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void ShapeAttribute::Set(FrameType frameType)
{
    animation_->SetAnimation(frameType, faceDirection_->GetDirection());
    animation_->ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

bool ShapeAttribute::AnimationIsCompleted() const
{
    return animation_->IsCompleted();
}

}  // namespace Entity

}  // namespace FA
