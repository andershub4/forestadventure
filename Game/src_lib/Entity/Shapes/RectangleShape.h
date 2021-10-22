/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicShape.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace FA {

namespace Entity {

class RectangleShape : public BasicShape
{
public:
    virtual void DrawTo(sf::RenderTarget &renderTarget) override;
    virtual void SetTransform(const sf::Vector2f &position, float scale) override;

    void SetSize(const sf::Vector2f &size);

private:
    sf::RectangleShape rShape_;
};

}  // namespace Entity

}  // namespace FA
