/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Animator/Animator.h"
#include "Body.h"
#include "RectangleShape.h"
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
    for (auto animator : imageAnimators_) {
        animator->Enter();
    }
    for (auto &sprite : sprites_) {
        sprite->setPosition(body_.position_);
        sprite->setRotation(body_.rotation_);
    }

    for (auto animator : colliderAnimators_) {
        animator->Enter();
    }
    for (auto &element : colliders_) {
        element.rect_->setPosition(body_.position_);
        element.rect_->setRotation(body_.rotation_);
    }

#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif
}

void Shape::Update(float deltaTime)
{
    for (auto animator : imageAnimators_) {
        animator->Update(deltaTime);
    }
    for (auto animator : colliderAnimators_) {
        animator->Update(deltaTime);
    }

    for (auto &sprite : sprites_) {
        sprite->setPosition(body_.position_);
        sprite->setRotation(body_.rotation_);
    }
    for (auto &element : colliders_) {
        element.rect_->setPosition(body_.position_);
        element.rect_->setRotation(body_.rotation_);
    }

#ifdef _DEBUG
    rShape_.setPosition(body_.position_);
#endif  // _DEBUG
}

std::shared_ptr<Graphic::SpriteIf> Shape::RegisterSprite()
{
    auto sprite = std::make_shared<Graphic::Sprite>();
    sprites_.push_back(sprite);

    return sprite;
}

std::shared_ptr<Graphic::RectangleShapeIf> Shape::RegisterCollider(ColliderType layer)
{
    auto rect = std::make_shared<Graphic::RectangleShape>();
    rect->setFillColor(sf::Color::Transparent);
    rect->setOutlineColor(sf::Color::Red);
    rect->setOutlineThickness(1.0f);
    colliders_.push_back({rect, layer});

    return rect;
}

void Shape::RegisterImageAnimator(std::shared_ptr<AnimatorIf<Shared::ImageFrame>> animator)
{
    imageAnimators_.push_back(animator);
}

void Shape::RegisterColliderAnimator(std::shared_ptr<AnimatorIf<Shared::ColliderFrame>> animator)
{
    colliderAnimators_.push_back(animator);
}

void Shape::DrawTo(Graphic::RenderTargetIf &renderTarget) const
{
    for (auto &sprite : sprites_) {
        renderTarget.draw(*sprite);
    }

#ifdef _DEBUG
    for (auto &element : colliders_) {
        renderTarget.draw(*element.rect_);
    }

    renderTarget.draw(rShape_);
#endif
}

bool Shape::Intersect(const Shape &otherShape) const
{
    bool intersect = false;

    for (auto &element : colliders_) {
        for (auto &otherElement : otherShape.colliders_) {
            if (element.layer_ == otherElement.layer_) {
                intersect |= element.rect_->getGlobalBounds().intersects(otherElement.rect_->getGlobalBounds());
            }
        }
    }

    return intersect;
}

}  // namespace Entity

}  // namespace FA
