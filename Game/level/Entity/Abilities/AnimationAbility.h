/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "Resource/Animation.h"

namespace FA {

namespace Entity {

class AnimationAbility
{
public:
    AnimationAbility(std::function<std::string()> getKey, std::function<void(const Shared::Animation &)>,
                     bool center = true);
    AnimationAbility(std::function<std::string()> getKey, bool center = true);
    virtual ~AnimationAbility();

    void Enter();
    void Update(float deltaTime);

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void RegisterAnimation(const std::string &name, const Shared::Animation &animation);
    void DrawTo(sf::RenderTarget &renderTarget);

private:
    std::unordered_map<std::string, Shared::Animation> map_;
    Shared::Animation currentAnimation_;
    std::function<std::string()> getKey_;
    std::function<void(const Shared::Animation &)> updateFn_;
    sf::Sprite sprite_;
    bool center_{};
};

}  // namespace Entity

}  // namespace FA
