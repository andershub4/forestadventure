/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "RenderTexture.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "DrawableIf.h"
#include "Texture.h"
#include "View.h"

namespace FA {

namespace Graphic {

RenderTexture::RenderTexture()
    : renderTexture_(std::make_unique<sf::RenderTexture>())
    , texture_(Texture::CreateWrapper(renderTexture_->getTexture()))
{}

RenderTexture::~RenderTexture() = default;

void RenderTexture::draw(const DrawableIf& drawable)
{
    const sf::Drawable& sfDrawable = drawable;
    return renderTexture_->draw(sfDrawable);
}

bool RenderTexture::create(unsigned int width, unsigned int height, bool depthBuffer)
{
    return renderTexture_->create(width, height, depthBuffer);
}

void RenderTexture::display()
{
    renderTexture_->display();
}

sf::Vector2u RenderTexture::getSize() const
{
    return renderTexture_->getSize();
}

const Graphic::TextureIf& RenderTexture::getTexture() const
{
    return *texture_;
}

void RenderTexture::clear()
{
    renderTexture_->clear(sf::Color(0, 0, 0, 255));
}

void RenderTexture::clear(const sf::Color& color)
{
    renderTexture_->clear(color);
}

void RenderTexture::setView(const Graphic::ViewIf& view)
{
    const sf::View& sfView = dynamic_cast<const View&>(view);
    renderTexture_->setView(sfView);
}

sf::Vector2f RenderTexture::mapPixelToCoords(const sf::Vector2i& point) const
{
    return renderTexture_->mapPixelToCoords(point);
}

}  // namespace Graphic

}  // namespace FA
