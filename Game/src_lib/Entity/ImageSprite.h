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
#include "Resource/Image.h"
#include "StateType.h"

namespace FA {

namespace Entity {

class ImageSprite
{
public:
    ImageSprite(std::function<std::string(StateType stateType)> getKey,
                std::function<void(ImageSprite &imageSprite)> beginImage);
    virtual ~ImageSprite();

    void RegisterImage(const std::string &name, const Image &image);
    void Enter(StateType stateType);
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    void ApplyTo(std::function<void(sf::Sprite &sprite)> applyFn);

private:
    std::unordered_map<std::string, Image> map_;
    sf::Sprite sprite_;
    Image currentImage_;
    std::function<std::string(StateType stateType)> getKey_;
    std::function<void(ImageSprite &imageSprite)> beginImage_;
};

}  // namespace Entity

}  // namespace FA
