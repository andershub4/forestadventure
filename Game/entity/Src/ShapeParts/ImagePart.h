/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "BasicShapePart.h"
#include "Logging.h"
#include "Sprite.h"
#include "Sprites/ImageSprite.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ImagePartWith : public BasicShapePart
{
public:
    static std::shared_ptr<ImagePartWith<KeyT>> Create(const Shared::ImageSprite &image, bool center = true,
                                                       bool isCollidable = true)
    {
        return std::make_shared<CtorHelper>(image, center, isCollidable);
    }

    virtual ~ImagePartWith() = default;

    virtual void Enter() override { currentImage_ = GetImage(lookupKey_); }

    virtual void Update(float deltaTime) override
    {
        currentImage_.Update(deltaTime);
        updateCB_(currentImage_);
    }

    virtual void ApplyTo(Graphic::SpriteIf &sprite) const override
    {
        currentImage_.ApplyTo(sprite);

        if (center_) {
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        }
    }

    virtual bool IsCollidable() const override { return isCollidable_; }

    void RegisterImage(const KeyT key, const Shared::ImageSprite &image)
    {
        auto res = map_.emplace(key, image);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::ImageSprite &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for singel image */
    ImagePartWith(const Shared::ImageSprite &image, bool center = true, bool isCollidable = true)
        : lookupKey_(defaultKey_)
        , defaultImage_(image)
        , currentImage_(defaultImage_)
        , updateCB_([](const Shared::ImageSprite &) {})
        , center_(center)
        , isCollidable_(isCollidable)
    {
        RegisterImage(defaultKey_, image);
    }

private:
    struct CtorHelper : public ImagePartWith<KeyT>
    {
        CtorHelper(const Shared::ImageSprite &image, bool center = true, bool isCollidable = true)
            : ImagePartWith<KeyT>(image, center, isCollidable)
        {}
    };

    KeyT defaultKey_{};
    Shared::ImageSprite defaultImage_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::ImageSprite> map_;
    Shared::ImageSprite currentImage_;
    std::function<void(const Shared::ImageSprite &)> updateCB_;
    bool center_{};
    bool isCollidable_{false};

private:
    Shared::ImageSprite GetImage(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }

        LOG_ERROR("Could not find %s", DUMP(key));
        return defaultImage_;
    }
};

using ImagePart = ImagePartWith<int>;

}  // namespace Entity

}  // namespace FA
