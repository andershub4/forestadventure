/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Effect.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace FA {

Effect::Effect(const sf::Vector2f& size)
    : size_(size)
{}

Effect::~Effect() = default;

}  // namespace FA
