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
#include "Logging.h"
#include "Resource/Image.h"

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

    virtual void Enter() override { currentImage_ = GetImage(defaultKey_); }

    virtual void Update(float deltaTime) override
    {
        if (currentImage_.IsValid()) {
            currentImage_.Update(deltaTime);
            currentImage_.ApplyTo(sprite_);
            sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
            updateCB_(currentImage_);
        }
    }

    void RegisterImage(const KeyT key, const Shared::Image &image) { map_[key] = image; }
    void RegisterUpdateCB(std::function<void(const Shared::Image &)> updateCB) { updateCB_ = updateCB; }

protected:
    ImageSpriteWith(const Shared::Image &image)
        : updateCB_([](const Shared::Image &) {})
    {
        RegisterImage(defaultKey_, image);
    }

private:
    template <class KeyT>
    struct CtorHelper : public ImageSpriteWith<KeyT>
    {
        CtorHelper(const Shared::Image &image)
            : ImageSpriteWith<KeyT>(image)
        {}
    };

    KeyT defaultKey_{};
    std::unordered_map<KeyT, Shared::Image> map_;
    Shared::Image currentImage_;
    std::function<void(const Shared::Image &)> updateCB_;

private:
    Shared::Image GetImage(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }
        else {
            LOG_ERROR("Could not find %s", DUMP(key));
        }

        return {};
    }
};

using ImageSprite = ImageSpriteWith<int>;

}  // namespace Entity

}  // namespace FA
