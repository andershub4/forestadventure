/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>

#include "Components/Movement/MovementComponent.h"
#include "Components/Sprite/SpriteComponent.h"
#include "Components/Transform/TransformComponent.h"
#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

struct Configuration
{
    FaceDirection faceDir_ = FaceDirection::Down;
    std::unique_ptr<TransformComponent> transform_ = nullptr;
    std::unique_ptr<MovementComponent> movement_ = nullptr;
    std::unique_ptr<SpriteComponent> sprite_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
