/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "RenderTargetIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class TextureIf;
class ViewIf;

class RenderTextureIf : public RenderTargetIf
{
public:
    virtual ~RenderTextureIf() override = default;
    virtual bool create(unsigned int width, unsigned int height, bool depthBuffer) = 0;
    virtual void display() = 0;
    virtual sf::Vector2u getSize() const = 0;
    virtual const Graphic::TextureIf& getTexture() const = 0;
    virtual void clear() = 0;
    virtual void clear(const sf::Color& color) = 0;
    virtual void setView(const Graphic::ViewIf& view) = 0;
    virtual sf::Vector2f mapPixelToCoords(const sf::Vector2i& point) const = 0;
};

}  // namespace Graphic

}  // namespace FA
