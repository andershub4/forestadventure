/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#ifdef _DEBUG
#include <SFML/Graphics/RectangleShape.hpp>
#endif

#include "Fwd/SfmlFwd.h"
#include "StateType.h"

namespace FA {

namespace Entity {

class AnimationSprite;
class ImageSprite;

class Shape
{
public:
    Shape(std::function<void(Shape &)> updateShape);
    virtual ~Shape();

    void OnEnterShape(StateType stateType);
    void OnExitShape(StateType stateType);
    void OnUpdateShape(float deltaTime);
    void OnDrawShape(sf::RenderTarget &renderTarget);

    std::shared_ptr<AnimationSprite> GetAnimationSprite(const std::string &name);
    std::shared_ptr<ImageSprite> GetImageSprite(const std::string &name);

    void RegisterAnimationSprite(const std::string &name, std::shared_ptr<AnimationSprite> sprite);
    void RegisterImageSprite(const std::string &name, std::shared_ptr<ImageSprite> sprite);

    void SetPosition(const sf::Vector2f &pos);

private:
#ifdef _DEBUG
    sf::RectangleShape rShape_;
#endif
    std::unordered_map<std::string, std::shared_ptr<AnimationSprite>> animations_;
    std::unordered_map<std::string, std::shared_ptr<ImageSprite>> images_;

    std::function<void(Shape &)> updateShape_;
};

}  // namespace Entity

}  // namespace FA
