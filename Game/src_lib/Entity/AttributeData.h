/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Enum/FaceDirection.h"
#include "Resource/Frame.h"

namespace FA {

namespace Entity {

struct AttributeData
{
    sf::Vector2f position_{};
    FaceDirection faceDir_{};
    float velocity_{};
    float scale_{};
    std::vector<Frame> frames_;
    Frame frame_;
};

}  // namespace Entity

}  // namespace FA
