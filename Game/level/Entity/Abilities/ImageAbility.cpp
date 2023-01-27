/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageAbility.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Logging.h"

namespace FA {

namespace Entity {

ImageAbility::ImageAbility(std::function<std::string()> getKey, std::function<void(const Shared::Image &)> updateFn)
    : getKey_(getKey)
    , updateFn_(updateFn)
{}

ImageAbility::ImageAbility(std::function<std::string()> getKey)
    : getKey_(getKey)
    , updateFn_([](const Shared::Image &) {})
{}

ImageAbility::~ImageAbility() = default;

void ImageAbility::Enter()
{
    auto key = getKey_();
    if (map_.find(key) != map_.end()) {
        currentImage_ = map_.at(key);
    }
    else {
        LOG_ERROR("Could not find key: %s", key.c_str());
    }
}

void ImageAbility::Update(float deltaTime)
{
    if (currentImage_.IsValid()) {
        currentImage_.Update(deltaTime);
        currentImage_.ApplyTo(sprite_);
        sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
        updateFn_(currentImage_);
    }
}

void ImageAbility::SetPosition(const sf::Vector2f &position)
{
    sprite_.setPosition(position);
}

void ImageAbility::SetRotation(float rot)
{
    sprite_.setRotation(rot);
}

void ImageAbility::RegisterImage(const std::string &name, const Shared::Image &image)
{
    if (map_.find(name) == map_.end()) {
        map_[name] = image;
    }
    else {
        LOG_ERROR("name: %s already exist", name.c_str());
    }
}

void ImageAbility::DrawTo(sf::RenderTarget &renderTarget)
{
    renderTarget.draw(sprite_);
}

}  // namespace Entity

}  // namespace FA
