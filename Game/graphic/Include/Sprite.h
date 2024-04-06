/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"
#include "SpriteIf.h"

namespace FA {

namespace Graphic {

class Sprite : public SpriteIf
{
public:
    Sprite();

    virtual void setTexture(const TextureIf &texture, bool resetRect = false) override;
    virtual void setTextureRect(const sf::IntRect &rectangle) override;
    virtual void setColor(const sf::Color &color) override;
    virtual const TextureIf *getTexture() const override;

    virtual sf::FloatRect getLocalBounds() const override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setPosition(float x, float y) override;
    virtual void setPosition(const sf::Vector2f &position) override;
    virtual void setRotation(float angle) override;

    virtual void setOrigin(float x, float y) override;

private:
    std::shared_ptr<sf::Sprite> sprite_;
    const TextureIf *texture_{nullptr};

private:
    virtual operator const sf::Drawable &() const override;
};

}  // namespace Graphic

}  // namespace FA
