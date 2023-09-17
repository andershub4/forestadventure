/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "ITexture.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class Texture : public ITexture
{
public:
    Texture();
    virtual ~Texture();

    static std::shared_ptr<const ITexture> CreateWrapper(const sf::Texture &texture)
    {
        return std::shared_ptr<Texture>(new Texture(texture));
    }

    virtual bool create(unsigned int width, unsigned int height) override;
    virtual bool loadFromFile(const std::string &filename) override;
    virtual bool loadFromFile(const std::string &filename, const sf::IntRect &area) override;
    virtual bool loadFromMemory(const void *data, std::size_t size) override;
    virtual bool loadFromMemory(const void *data, std::size_t size, const sf::IntRect &area) override;

    virtual sf::Vector2u getSize() const override;

private:
    std::shared_ptr<sf::Texture> internalTexture_;
    sf::Texture *texture_{nullptr};

    friend class Sprite;

private:
    /* Since this constructor cast away the const from sf::Texture,
     * it is declared private and only used together with CreateWrapper
     * to ensure the constructed object is a const object.
     */
    Texture(const sf::Texture &texture);
    operator const sf::Texture &() const { return *texture_; };
};

}  // namespace Graphic

}  // namespace FA
