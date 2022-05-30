/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Shape.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "AnimationSprite.h"
#include "ImageSprite.h"

namespace FA {

namespace Entity {

Shape::Shape()
{
#ifdef _DEBUG
    rShape_.setSize({1.0, 1.0});
#endif
}

Shape::~Shape() = default;

void Shape::OnEnterAnimation(StateType stateType, const std::string &name)
{
    animations_.at(name)->Enter(stateType);
}

void Shape::OnExitAnimation(StateType stateType, const std::string &name)
{
    animations_.at(name)->Exit(stateType);
}

void Shape::OnUpdateAnimation(const std::string &animationStr, float deltaTime,
                              std::function<void(std::shared_ptr<AnimationSprite>)> stateFn)
{
    auto s = animations_.at(animationStr);
    s->Update(deltaTime);
    if (stateFn) stateFn(s);
}

void Shape::OnDrawAnimation(const std::string &name, sf::RenderTarget &renderTarget)
{
    auto s = animations_.at(name);
    s->DrawTo(renderTarget);
}

void Shape::OnEnterImage(StateType stateType, const std::string &name)
{
    auto s = images_.at(name);
    s->Enter(stateType);
}

void Shape::OnExitImage(StateType stateType, const std::string &name)
{
    auto s = images_.at(name);
    s->Exit(stateType);
}

void Shape::OnUpdateImage(const std::string &name, float deltaTime,
                          std::function<void(std::shared_ptr<ImageSprite>)> stateFn)
{
    auto s = images_.at(name);
    s->Update(deltaTime);
    if (stateFn) stateFn(s);
}

void Shape::OnDrawImage(const std::string &name, sf::RenderTarget &renderTarget)
{
    auto s = images_.at(name);
    s->DrawTo(renderTarget);
}

void Shape::RegisterAnimationSprite(const std::string &name, std::shared_ptr<AnimationSprite> s)
{
    animations_[name] = s;
}

void Shape::RegisterImageSprite(const std::string &name, std::shared_ptr<ImageSprite> s)
{
    images_[name] = s;
}

}  // namespace Entity

}  // namespace FA
