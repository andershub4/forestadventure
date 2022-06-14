/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "Resource/Animation.h"
#include "StateType.h"

namespace FA {

namespace Entity {

class AnimationSprite
{
public:
    AnimationSprite(std::function<std::string(StateType stateType)> getKey);
    virtual ~AnimationSprite();

    void RegisterAnimation(const std::string &name, const Animation &animation);
    void Enter(StateType stateType);
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    bool AnimationIsCompleted() const;
    void ApplyTo(std::function<void(sf::Sprite &sprite)> applyFn);

private:
    std::unordered_map<std::string, Animation> map_;
    sf::Sprite sprite_;
    Animation currentAnimation_;
    std::function<std::string(StateType stateType)> getKey_;
};

}  // namespace Entity

}  // namespace FA
