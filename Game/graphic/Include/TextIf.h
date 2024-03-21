/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <string>

#include "DrawableIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class FontIf;

class TextIf : public DrawableIf
{
public:
    virtual ~TextIf() = default;
    virtual void setString(const std::string &string) = 0;
    virtual void setFont(const Graphic::FontIf &font) = 0;
    virtual void setCharacterSize(unsigned int size) = 0;
    virtual void setFillColor(const sf::Color &color) = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
};

}  // namespace Graphic

}  // namespace FA
