/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "SfmlFwd.h"
#include "TextIf.h"

namespace FA {

namespace Graphic {

class Text : public TextIf
{
public:
    Text();
    virtual ~Text();

    virtual void setString(const std::string &string) override;
    virtual void setFont(const Graphic::FontIf &font) override;
    virtual void setCharacterSize(unsigned int size) override;
    virtual void setFillColor(const sf::Color &color) override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setPosition(const sf::Vector2f &position) override;

private:
    std::shared_ptr<sf::Text> text_;

private:
    virtual operator const sf::Drawable &() const override;
};

}  // namespace Graphic

}  // namespace FA
