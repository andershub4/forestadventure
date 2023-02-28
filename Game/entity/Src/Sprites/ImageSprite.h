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
#include "ResourceTable.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ImageSprite : public BasicSprite
{
public:
    ImageSprite(std::function<KeyT()> keyFn, std::function<void(const Shared::Image &)> updateFn)
        : table_(keyFn)
        , updateFn_(updateFn)
    {}
    ImageSprite(std::function<KeyT()> keyFn)
        : table_(keyFn)
        , updateFn_([](const Shared::Image &) {})
    {}

    virtual ~ImageSprite() = default;

    virtual void Enter() override { currentImage_ = table_.GetResource(); }

    virtual void Update(float deltaTime) override
    {
        if (currentImage_.IsValid()) {
            currentImage_.Update(deltaTime);
            currentImage_.ApplyTo(sprite_);
            sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
            updateFn_(currentImage_);
        }
    }

    void RegisterImage(const KeyT &key, const Shared::Image &image) { table_.RegisterResource(key, image); }

private:
    ResourceTable<KeyT, Shared::Image> table_;
    Shared::Image currentImage_;
    std::function<void(const Shared::Image &)> updateFn_;
};

}  // namespace Entity

}  // namespace FA
