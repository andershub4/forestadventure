/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace FA {

class Layer
{
public:
    Layer();
    void Draw(const sf::Drawable& drawable);
    void Display();
    void Clear();
    void DrawTo(sf::RenderTarget& renderTarget);

private:
    sf::Sprite sprite_;
    sf::RenderTexture renderTexture_;
};

}  // namespace FA
