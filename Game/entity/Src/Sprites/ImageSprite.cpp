/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageSprite.h"

#include "Logging.h"

namespace FA {

namespace Entity {

ImageSprite::ImageSprite(std::function<std::string()> getKey,
                         const std::unordered_map<std::string, Shared::Image> &images,
                         std::function<void(const Shared::Image &)> updateFn)
    : getKey_(getKey)
    , map_(images)
    , updateFn_(updateFn)
{}

ImageSprite::ImageSprite(std::function<std::string()> getKey,
                         const std::unordered_map<std::string, Shared::Image> &images)
    : getKey_(getKey)
    , map_(images)
    , updateFn_([](const Shared::Image &) {})
{}

ImageSprite::~ImageSprite() = default;

void ImageSprite::Enter()
{
    auto key = getKey_();
    if (map_.find(key) != map_.end()) {
        currentImage_ = map_.at(key);
    }
    else {
        LOG_ERROR("Could not find key: %s", key.c_str());
    }
}

void ImageSprite::Update(float deltaTime)
{
    if (currentImage_.IsValid()) {
        currentImage_.Update(deltaTime);
        currentImage_.ApplyTo(sprite_);
        sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
        updateFn_(currentImage_);
    }
}

}  // namespace Entity

}  // namespace FA
