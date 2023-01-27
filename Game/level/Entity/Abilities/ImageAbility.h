/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>

#include "Fwd/SfmlFwd.h"
#include "Resource/Image.h"

namespace FA {

namespace Entity {

class ImageAbility
{
public:
    ImageAbility(std::function<std::string()> getKey, std::function<void(const Shared::Image &)>);
    ImageAbility(std::function<std::string()> getKey);
    virtual ~ImageAbility();

    void Enter();
    void Update(float deltaTime);

    void SetPosition(const sf::Vector2f &position);
    void SetRotation(float rot);
    void RegisterImage(const std::string &name, const Shared::Image &image);
    void DrawTo(sf::RenderTarget &renderTarget);

private:
    std::unordered_map<std::string, Shared::Image> map_;
    Shared::Image currentImage_;
    std::function<std::string()> getKey_;
    std::function<void(const Shared::Image &)> updateFn_;
    sf::Sprite sprite_;
};

}  // namespace Entity

}  // namespace FA
