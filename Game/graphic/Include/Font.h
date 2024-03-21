/*
 *	Copyright (C) 2023 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "FontIf.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class Font : public FontIf
{
public:
    Font();
    virtual ~Font();

    virtual bool loadFromFile(const std::string &filename) override;

private:
    std::shared_ptr<sf::Font> font_;

    friend class Text;

private:
    operator const sf::Font &() const { return *font_; };
};

}  // namespace Graphic

}  // namespace FA
