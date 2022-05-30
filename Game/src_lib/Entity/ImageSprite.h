/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
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
    ImageSprite(std::function<void(StateType, ImageSprite &)> beginImage,
                std::function<void(ImageSprite &)> updateImage);
    virtual ~ImageSprite();

    void Enter(StateType stateType);
    void Exit(StateType stateType);

    void RegisterImage(const std::string &name, const Image &image);
    void Update(float deltaTime);

    void DrawTo(sf::RenderTarget &renderTarget);
    void ApplyTo(std::function<void(sf::Sprite &sprite)> applyFn);

    void SetImage(const std::string &key);

private:
    std::function<void(StateType, ImageSprite &)> beginImage_;
    std::function<void(ImageSprite &)> updateImage_;

    std::unordered_map<std::string, Image> map_;
    sf::Sprite sprite_;
    Image currentImage_;
};

}  // namespace Entity

}  // namespace FA
