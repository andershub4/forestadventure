/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "RenderTargetIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class SpriteIf;

}  // namespace Graphic

namespace Shared {

template <class CoolSpriteIfT>
class BasicCoolSprite : public CoolSpriteIfT
{
public:
    BasicCoolSprite(std::shared_ptr<Graphic::SpriteIf> sprite)
        : sprite_(sprite)
    {}

    virtual void Update(float deltaTime) override {}
    virtual void SetPosition(const sf::Vector2f& position) final { sprite_->setPosition(position); }
    virtual void SetRotation(float rot) final { sprite_->setRotation(rot); }
    virtual void DrawTo(Graphic::RenderTargetIf& renderTarget) const final { renderTarget.draw(*sprite_); }
    virtual void Center() final
    {
        sprite_->setOrigin(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
    }

protected:
    std::shared_ptr<Graphic::SpriteIf> sprite_;
};

}  // namespace Shared

}  // namespace FA
