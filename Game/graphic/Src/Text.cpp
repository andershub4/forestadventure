/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Text.h"

#include <SFML/Graphics/Text.hpp>

#include "Font.h"

namespace FA {

namespace Graphic {

Text::Text()
    : text_(std::make_shared<sf::Text>())
{}

Text::~Text() = default;

void Text::setString(const std::string &string)
{
    text_->setString(string);
}

void Text::setFont(const Graphic::IFont &font)
{
    const sf::Font &sfFont = dynamic_cast<const Font &>(font);
    text_->setFont(sfFont);
}

void Text::setCharacterSize(unsigned int size)
{
    text_->setCharacterSize(size);
}

void Text::setFillColor(const sf::Color &color)
{
    text_->setFillColor(color);
}

sf::FloatRect Text::getGlobalBounds() const
{
    return text_->getGlobalBounds();
}

void Text::setPosition(const sf::Vector2f &position)
{
    text_->setPosition(position);
}

Text::operator const sf::Drawable &() const
{
    return *text_;
}

}  // namespace Graphic

}  // namespace FA
