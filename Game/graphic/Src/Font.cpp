/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Font.h"

#include <SFML/Graphics/Font.hpp>

namespace FA {

namespace Graphic {

Font::Font()
    : font_(std::make_shared<sf::Font>())
{}

Font::~Font() = default;

bool Font::loadFromFile(const std::string &string)
{
    return font_->loadFromFile(string);
}

}  // namespace Graphic

}  // namespace FA
