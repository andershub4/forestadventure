/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageShape.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

namespace Entity {

ImageShape::ImageShape(std::function<std::string(FrameType, FaceDirection)> lookupKeyFunc)
    : lookupKeyFunc_(lookupKeyFunc)
{}

void ImageShape::Update(float deltaTime)
{}

void ImageShape::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

void ImageShape::AddImage(FrameType frameType, FaceDirection faceDir, const Image &image)
{
    auto k = lookupKeyFunc_(frameType, faceDir);
    imageMap_[k] = image;
}

void ImageShape::SetImage(FrameType frameType, FaceDirection faceDir)
{
    auto k = lookupKeyFunc_(frameType, faceDir);
    auto image = imageMap_.at(k);
    image.ApplyTo(sprite_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
}

void ImageShape::SetTransform(const sf::Vector2f &position, float scale)
{
    sprite_.setPosition(position);
    sprite_.setScale(scale, scale);
}

}  // namespace Entity

}  // namespace FA
