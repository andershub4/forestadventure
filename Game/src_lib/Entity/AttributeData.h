/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

struct AttributeData
{
    sf::Vector2f position_{};
    FaceDirection faceDir_{};
    float velocity_{};
    float scale_{};
};

}  // namespace Entity

}  // namespace FA
