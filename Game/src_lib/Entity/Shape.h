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
    Shape();
    virtual ~Shape();

    void OnEnterAnimation(StateType stateType, const std::string &name);
    void OnExitAnimation(StateType stateType, const std::string &name);
    void OnUpdateAnimation(const std::string &name, float deltaTime,
                           std::function<void(std::shared_ptr<AnimationSprite>)> stateFn);
    void OnDrawAnimation(const std::string &name, sf::RenderTarget &renderTarget);

    void OnEnterImage(StateType stateType, const std::string &name);
    void OnExitImage(StateType stateType, const std::string &name);
    void OnUpdateImage(const std::string &name, float deltaTime,
                       std::function<void(std::shared_ptr<ImageSprite>)> stateFn);
    void OnDrawImage(const std::string &name, sf::RenderTarget &renderTarget);

    void RegisterAnimationSprite(const std::string &name, std::shared_ptr<AnimationSprite> sprite);
    void RegisterImageSprite(const std::string &name, std::shared_ptr<ImageSprite> sprite);

private:
#ifdef _DEBUG
    sf::RectangleShape rShape_;
#endif
    std::unordered_map<std::string, std::shared_ptr<AnimationSprite>> animations_;
    std::unordered_map<std::string, std::shared_ptr<ImageSprite>> images_;
};

}  // namespace Entity

}  // namespace FA
