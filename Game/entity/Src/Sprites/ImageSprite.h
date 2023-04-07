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
class ImageSpriteWith : public BasicSprite
{
public:
    static std::shared_ptr<ImageSpriteWith<KeyT>> Create(const Shared::Image &image)
    {
        return std::make_shared<CtorHelper<KeyT>>(image);
    }

    virtual ~ImageSpriteWith() = default;

    virtual void Enter() override { currentImage_ = table_.GetResource(defaultKey); }

    virtual void Update(float deltaTime) override
    {
        if (currentImage_.IsValid()) {
            currentImage_.Update(deltaTime);
            currentImage_.ApplyTo(sprite_);
            sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
            updateCB_(currentImage_);
        }
    }

    void RegisterUpdateCB(std::function<void(const Shared::Image &)> updateCB) { updateCB_ = updateCB; }

protected:
    ImageSpriteWith(const Shared::Image &image)
        : updateCB_([](const Shared::Image &) {})
    {
        table_.RegisterResource(defaultKey, image);
    }

private:
    template <class KeyT>
    struct CtorHelper : public ImageSpriteWith<KeyT>
    {
        CtorHelper(const Shared::Image &image)
            : ImageSpriteWith<KeyT>(image)
        {}
    };

    KeyT defaultKey{};
    ResourceTable<KeyT, Shared::Image> table_;
    Shared::Image currentImage_;
    std::function<void(const Shared::Image &)> updateCB_;
};

using ImageSprite = ImageSpriteWith<int>;

}  // namespace Entity

}  // namespace FA
