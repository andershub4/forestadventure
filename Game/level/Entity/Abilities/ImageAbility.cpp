/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ImageAbility.h"

#include "Logging.h"

namespace FA {

namespace Entity {

ImageAbility::ImageAbility(std::function<std::string()> getKey, std::function<void(const Shared::Image &)> updateFn)
    : getKey_(getKey)
    , updateFn_(updateFn)
{}

ImageAbility::~ImageAbility() = default;

void ImageAbility::Enter(std::shared_ptr<BasicEvent> event)
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
        updateFn_(currentImage_);
    }
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

}  // namespace Entity

}  // namespace FA
