/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "SFML/System/Vector2.hpp"

#include "BasicShapePart.h"
#include "Logging.h"
#include "Sprite.h"
#include "Texture.h"

namespace FA {

namespace Entity {

template <class KeyT>
class NoShapePartWith : public BasicShapePart
{
public:
    static std::shared_ptr<NoShapePartWith<KeyT>> Create(const sf::Vector2i &size, bool center = true,
                                                         bool isCollidable = true)
    {
        return std::make_shared<CtorHelper>(size, center, isCollidable);
    }

    static std::shared_ptr<NoShapePartWith<KeyT>> Create(KeyT &lookupKey, bool center = true, bool isCollidable = true)
    {
        return std::make_shared<CtorHelper>(lookupKey, center, isCollidable);
    }

    virtual ~NoShapePartWith() = default;

    virtual void Enter() override { currentTexture_ = GetTexture(lookupKey_); }

    virtual void Update(float deltaTime) override { updateCB_(currentTexture_); }

    virtual void ApplyTo(Graphic::SpriteIf &sprite) const override
    {
        sprite.setTexture(currentTexture_);

        if (center_) {
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        }
    }

    virtual bool IsDrawable() const override { return false; }

    virtual bool IsCollidable() const override { return isCollidable_; }

    void RegisterHitbox(const KeyT key, const sf::Vector2i &size)
    {
        Graphic::Texture texture;
        texture.create(size.x, size.y);

        auto res = map_.emplace(key, texture);
        if (!res.second) {
            LOG_WARN("%s is already inserted", DUMP(key));
        }
    }
    void RegisterUpdateCB(std::function<void(const Shared::AnimationSprite &)> updateCB) { updateCB_ = updateCB; }

private:
    /* Constructor for multiple rects, depending on KeyT */
    NoShapePartWith(KeyT &lookupKey, bool center = true, bool isCollidable = true)
        : lookupKey_(lookupKey)
        , updateCB_([](const Graphic::Texture &) {})
        , center_(center)
        , isCollidable_(isCollidable)
    {
        defaultTexture_.create(10, 10);
        currentTexture_ = defaultTexture_;
    }

    /* Constructor for singel rect */
    NoShapePartWith(const sf::Vector2i &size, bool center = true, bool isCollidable = true)
        : lookupKey_(defaultKey_)
        , updateCB_([](const Graphic::Texture &) {})
        , center_(center)
        , isCollidable_(isCollidable)
    {
        defaultTexture_.create(size.x, size.y);
        currentTexture_ = defaultTexture_;
        RegisterHitbox(defaultKey_, size);
    }

private:
    struct CtorHelper : public NoShapePartWith<KeyT>
    {
        CtorHelper(KeyT &lookupKey, bool center = true, bool isCollidable = true)
            : NoShapePartWith<KeyT>(lookupKey, center, isCollidable)
        {}

        CtorHelper(const sf::Vector2i &size, bool center = true, bool isCollidable = true)
            : NoShapePartWith<KeyT>(size, center, isCollidable)
        {}
    };

    KeyT defaultKey_{};
    Graphic::Texture defaultTexture_;
    KeyT &lookupKey_;
    std::unordered_map<KeyT, Graphic::Texture> map_;
    Graphic::Texture currentTexture_;
    std::function<void(const Graphic::Texture &)> updateCB_;
    bool center_{};
    bool isCollidable_{false};

private:
    Graphic::Texture GetTexture(const KeyT &key)
    {
        if (map_.find(key) != map_.end()) {
            return map_.at(key);
        }

        LOG_ERROR("Could not find %s", DUMP(key));
        return defaultTexture_;
    }
};

using NoShapePart = NoShapePartWith<int>;

}  // namespace Entity

}  // namespace FA
