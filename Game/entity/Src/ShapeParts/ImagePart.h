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
#include "IRenderTarget.h"
#include "Logging.h"
#include "Sprite.h"
#include "Sprites/ImageSprite.h"

namespace FA {

namespace Entity {

template <class KeyT>
class ImagePartWith : public BasicShapePart
{
public:
    static std::shared_ptr<ImagePartWith<KeyT>> Create(const Shared::ImageSprite &image)
    {
        return std::make_shared<CtorHelper>(image);
    }

    virtual ~ImagePartWith() = default;

    virtual void Enter() override { currentImage_ = GetImage(lookupKey_); }

    virtual void Update(float deltaTime) override
    {
        currentImage_.Update(deltaTime);
        if (true) {
            currentImage_.Center();
        }
        updateCB_(currentImage_);
    }

    virtual void SetPosition(const sf::Vector2f &position) override { currentImage_.SetPosition(position); }
    virtual void SetRotation(float rot) override { currentImage_.SetRotation(rot); }
    virtual void DrawTo(Graphic::IRenderTarget &renderTarget) const override { currentImage_.DrawTo(renderTarget); }

    void RegisterImage(const KeyT key, const Shared::ImageSprite &image)
    {
        auto res = map_.emplace(key, image);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::ImageSprite &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for singel animation */
    ImagePartWith(const Shared::ImageSprite &image)
        : lookupKey_(defaultKey_)
        , defaultImage_(image)
        , currentImage_(defaultImage_)
        , updateCB_([](const Shared::ImageSprite &) {})
    {
        RegisterImage(defaultKey_, image);
    }

private:
    struct CtorHelper : public ImagePartWith<KeyT>
    {
        CtorHelper(const Shared::ImageSprite &image)
            : ImagePartWith<KeyT>(image)
        {}
    };

    KeyT defaultKey_{};
    Shared::ImageSprite defaultImage_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Shared::ImageSprite> map_;
    Shared::ImageSprite currentImage_;
    std::function<void(const Shared::ImageSprite &)> updateCB_;

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
