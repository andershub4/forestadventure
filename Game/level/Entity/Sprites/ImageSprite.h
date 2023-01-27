/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicSprite.h"
#include "Resource/Image.h"

namespace FA {

namespace Entity {

class ImageSprite : public BasicSprite
{
public:
    ImageSprite(std::function<std::string()> getKey, const std::unordered_map<std::string, Shared::Image> &images, std::function<void(const Shared::Image &)>);
    ImageSprite(std::function<std::string()> getKey, const std::unordered_map<std::string, Shared::Image> &images);
    virtual ~ImageSprite();

    virtual void Enter() override;
    virtual void Update(float deltaTime) override;

private:
    std::unordered_map<std::string, Shared::Image> map_;
    Shared::Image currentImage_;
    std::function<std::string()> getKey_;
    std::function<void(const Shared::Image &)> updateFn_;
};

}  // namespace Entity

}  // namespace FA
