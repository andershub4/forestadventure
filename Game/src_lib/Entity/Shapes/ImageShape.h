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

#include "Animation/Image.h"
#include "Enum/FaceDirection.h"
#include "Enum/FrameType.h"

namespace FA {

namespace Entity {

class ImageShape
{
public:
    ImageShape(std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc);

    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget &renderTarget);

    void AddImage(FrameType frameType, FaceDirection faceDir, const Image &image);
    void SetImage(FrameType frameType, FaceDirection faceDir);
    void SetTransform(const sf::Vector2f &position, float scale);

private:
    std::unordered_map<std::string, Image> imageMap_;
    sf::Sprite sprite_;
    std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc_;
};

}  // namespace Entity

}  // namespace FA
